import { demoArticles } from "@/constants/Articles";
import { Article } from "@/domain/Article";
import { createContext, ReactNode, useEffect, useState } from "react";
import * as SQLite from "expo-sqlite";
import { addArticleDb, addToSyncQueue, clearArticleDb, clearSyncQueue, deleteArticleDb, syncPendingOperations, updateArticleDb } from "@/repository/SQLRepository";
import { showMessage } from "react-native-flash-message";
import { getArticleCategoryFromString } from "@/domain/ArticleCategory";
import { addArticleToServer, deleteArticleFromServer, getAllFromServer, updateArticleOnServer } from "@/repository/NetworkRepository";


export type ArticleContextProps = {
  articles: Article[];
  addArticle: (article: Article) => void;
  updateArticle: (article: Article) => void;
  deleteArticle: (articleId: number) => void;
  getArticle: (articleId: number) => Article | undefined;
};

export type ArticleContextProviderType = {
  children: ReactNode;
};

export const ArticleContext = createContext<ArticleContextProps | null>(null);

export default function ArticleContextProvider({
  children,
}: ArticleContextProviderType) {
  const [articles, setArticles] = useState<Article[]>([]);
  const [dbConnection, setDbConnection] = useState<SQLite.SQLiteDatabase>();

  const addArticle = async (article: Article) => {
    try {
      const insertedArticle = await addArticleToServer(article);
      await addArticleDb(dbConnection!, article, insertedArticle?.articleId)
      setArticles([...articles, insertedArticle!]);
    }
    catch(error){
      throw new Error("Failed to add article to database");
    };
  }

  const updateArticle = async (articleToUpdate: Article) => {
    try {
      await updateArticleDb(dbConnection!, articleToUpdate);

      setArticles((prevArticles) =>
        prevArticles.map((article) =>
          article.articleId === articleToUpdate.articleId ? articleToUpdate : article
        )
      );

      try {
        await updateArticleOnServer(articleToUpdate);
      } catch (serverError) {
        console.log("Failed to update on server:", serverError);

        await addToSyncQueue(
          dbConnection!,
          articleToUpdate.articleId,
          "UPDATE",
          JSON.stringify(articleToUpdate)
        );
      }
    } catch (dbError) {
      console.error("Failed to update task locally:", dbError);
      throw new Error("Task update failed.");
    }
  };

  const deleteArticle = async (articleId: number) => {
    try {
      await deleteArticleDb(dbConnection!, articleId);

      setArticles((prevArticles) =>
        prevArticles.filter((article) => article.articleId !== articleId)
      );

      try {
        await deleteArticleFromServer(articleId);
      } catch (serverError) {
        console.error("Failed to delete on server:", serverError);

        // Add to Sync Queue
        await addToSyncQueue(dbConnection!, articleId, "DELETE", "");
      }
    } catch (dbError) {
      console.error("Failed to delete article locally:", dbError);
      throw new Error("Article deletion failed.");
    }
  };

  const getArticle = (articleId: number) => {
    const article = articles.find((article) => articleId == article.articleId);

    return article;
  };


  useEffect(() => {
    const db = SQLite.openDatabaseSync("articles.db");
    setDbConnection(db);
    createTable(db);

    async function  getAll() {
      try{
        console.log("start fetch tasks");
        try {
          //  addAllDemoArticles(db);
          await fetchArticlesFromServer();
        } catch (error) {
          console.log("fetch from server failed...");
          console.log("fetching from local db");
          await fetchArticles(db);
        }
        //addAllDemoArticles(db);
      } catch (error) {
        console.error("Failed to fetch articles from database");
  
        showMessage({
          message: "Failed to fetch articles from database",
          type: "warning",
          duration: 2000,
        });
      }
  
    }
  
    getAll();

    const syncInterval = setInterval(() => {
      syncPendingOperations(db);
    }, 1000); // Sync every 60 seconds
    return () => clearInterval(syncInterval);
  }, []);

  const addAllDemoArticles = async (connection: SQLite.SQLiteDatabase) => {
    for (const article of demoArticles) {
      await addArticleToServer(article)
        .then(() => {
          console.log("Demo article added:", article);
        })
        .catch((error) => {
          console.error("Error adding demo article:", error);
        });
    }
    fetchArticles(connection); 
  };

  // websocket
  useEffect(() => {
    const socket = new WebSocket("ws://192.168.38.97:3001");
    socket.onopen = () => {
      console.log("WebSocket connection established");
    };

    socket.onmessage = async (event) => {
      const { type, payload } = JSON.parse(event.data);

      if (type === "add") {
        const articleToAdd: Article = {
          articleId: payload.articleId,
          title: payload.title,
          context: payload.context,
          author: payload.author,
          date: new Date(payload.date),
          category: getArticleCategoryFromString(payload.category),
        };

        await addArticleDb(dbConnection!, articleToAdd, articleToAdd.articleId);

        setArticles((prevArticles) => [...prevArticles, articleToAdd]);
      } else if (type === "update") {
        const updatedArticle: Article = {
          articleId: payload.articleId,
          title: payload.title,
          context: payload.context,
          author: payload.author,
          date: new Date(payload.date),
          category: getArticleCategoryFromString(payload.category),
        };

        await updateArticleDb(dbConnection!, payload);
        setArticles((prevArticles) =>
          prevArticles.map((article) =>
            article.articleId == updatedArticle.articleId ? updatedArticle : article
          )
        );
      } else if (type === "delete") {
        setArticles((prevArticles) =>
          prevArticles.filter((article) => article.articleId != payload.articleId)
        );
      }
    };

    socket.onerror = (error) => {
      console.error("WebSocket error:", error);
    };

    socket.onclose = () => {
      console.log("WebSocket connection closed");
    };

    return () => {
      socket.close();
    };
  }, []);


  const createTable = (connection: SQLite.SQLiteDatabase) => {
    connection.execSync(
      "CREATE TABLE IF NOT EXISTS articles(\
      articleId INTEGER PRIMARY KEY AUTOINCREMENT,\
      title TEXT NOT NULL,\
      context TEXT NOT NULL,\
      author TEXT NOT NULL,\
      date TEXT NOT NULL,\
      category TEXT NOT NULL);"
    );

    connection.execSync(
      `CREATE TABLE IF NOT EXISTS sync_queue (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        articleId INTEGER NOT NULL,
        syncAction TEXT NOT NULL,
        payload TEXT NOT NULL
      );`
    );
  };
  

    const fetchArticlesFromServer = async () => {
      let articles = await getAllFromServer();
      console.log("Fetched articles from server:", articles);
      setArticles(articles);
      await clearArticleDb(dbConnection!);
      articles.forEach((article: Article) => {
        addArticleDb(dbConnection!, article, article.articleId);
      });
      console.log("fetched articles from server!");
    };

    const fetchArticles = async (connection: SQLite.SQLiteDatabase) => {
      const allArticles = await connection.getAllAsync("SELECT * FROM articles");
      const articles: Article[] = [];
  
      for (const article of allArticles) {
        const articleId = (article as any).articleId;
        const title = (article as any).title;
        const context = (article as any).context;
        const author = (article as any).author;
        const date = new Date((article as any).date);
        const category = getArticleCategoryFromString((article as any).category);
  
        const currentArticle: Article = {
          articleId: articleId,
          title: title,
          context: context,
          author: author,
          date: date,
          category: category,
        };
  
        articles.push(currentArticle);
      }
  
      setArticles(articles);
    };

  return (
    <ArticleContext.Provider
      value={{
        articles: articles,
        addArticle: addArticle,
        updateArticle: updateArticle,
        deleteArticle: deleteArticle,
        getArticle: getArticle,
      }}
    >
      {children}
    </ArticleContext.Provider>
  );
}