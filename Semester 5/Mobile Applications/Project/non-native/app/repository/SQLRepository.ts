import { Article } from "@/domain/Article";
import { SQLiteDatabase } from "expo-sqlite";
import { deleteArticleFromServer, updateArticleOnServer } from "./NetworkRepository";

export async function addArticleDb(dbConnection: SQLiteDatabase, article: Article, articleId?: number) {
  if (articleId == undefined)
    return dbConnection
      ?.runAsync(
        "INSERT INTO articles (title, context, author, date, category) values (?, ?, ?, ?, ?)",
        article.title,
        article.context,
        article.author,
        article.date.toISOString(),
        article.category 
      );


      return dbConnection
      ?.runAsync(
        "INSERT OR REPLACE INTO articles (title, context, author, date, category) values (?, ?, ?, ?, ?)",
        article.title,
        article.context,
        article.author,
        article.date.toISOString(),
        article.category 
      );
}

export async function updateArticleDb(dbConnection: SQLiteDatabase, articleToUpdate: Article) {
  return dbConnection
    ?.runAsync(
      `UPDATE articles 
       SET title = ?, context = ?, author = ?, date = ?, category = ? 
       WHERE articleId = ?`,
      articleToUpdate.title,
      articleToUpdate.context,
      articleToUpdate.author,
      articleToUpdate.date.toISOString(),
      articleToUpdate.category,
      articleToUpdate.articleId
    );
}

export async function deleteArticleDb(dbConnection: SQLiteDatabase, articleId: number) {
  return dbConnection
    ?.runAsync("DELETE FROM articles WHERE articleId = ?", articleId);
}

export async function clearArticleDb(dbConnection: SQLiteDatabase) {
  return dbConnection
    ?.runAsync("DELETE FROM articles");
}


export const addToSyncQueue = async (
  connection: SQLiteDatabase,
  articleId: number,
  syncAction: string,
  payload: string
) => {
  await connection.runAsync(
    `INSERT INTO sync_queue (articleId, syncAction, payload)
     VALUES (?, ?, ?);`,
    [articleId, syncAction, payload]
  );
};

export const clearSyncQueue = async (connection: SQLiteDatabase) => {
  await connection.runAsync(`DELETE FROM sync_queue`);
}

export const getSyncQueue = async (
  connection: SQLiteDatabase
): Promise<{ id: number; articleId: number; syncAction: string; payload: string }[]> => {
  const result = await connection.getAllAsync(`SELECT * FROM sync_queue`);
  return result.map((row: any) => ({
    id: row.id,
    articleId: row.articleId,
    syncAction: row.syncAction,
    payload: row.payload,
  }));
};

export const removeFromSyncQueue = async (
  connection: SQLiteDatabase,
  id: number
) => {
  await connection.runAsync(`DELETE FROM sync_queue WHERE articleId = ?;`, [id]);
};

export const syncPendingOperations = async (dbConnection: SQLiteDatabase) => {
  try {
    const pendingOperations = await getSyncQueue(dbConnection);

    for (const operation of pendingOperations) {
      const { id, articleId, syncAction, payload } = operation;

      try {
        if (syncAction === "UPDATE" && payload) {
          const article = JSON.parse(payload);
          const newArticle = {
            ...article,
            date : new Date(article.date)
          }
          
          await updateArticleOnServer(newArticle);
        } else if (syncAction === "DELETE") {
          await deleteArticleFromServer(articleId);
        }

        // Remove successfully synced operation from the queue
        await removeFromSyncQueue(dbConnection!, id);
      } catch (syncError) {
        console.error(`Failed to sync operation with id ${id}:`, syncError);
      }
    }
  } catch (error) {
    console.error("Error fetching pending operations from sync_queue:", error);
  }
};