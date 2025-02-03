import ArticleContextProvider from "@/context/ArticleContext";
import { Article } from "@/domain/Article";

const BASE_API_URL = 'http://192.168.38.97:3000';

export async function getAllFromServer() {  
    const controller = new AbortController();
    const timeout = 2000;
    const timeoutId = setTimeout(() => controller.abort(), timeout);

    try {
    const response = await fetch(BASE_API_URL + '/articles', {signal: controller.signal});
    const articles: Article[] = await response.json();

    console.log("Raw response from API:", articles);

    return articles.map((article: any) => ({
        articleId: article.articleId,
        title: article.title,
        context: article.context,
        author: article.author,
        date: new Date(article.date),
        category: article.category,
      }));

    }
    catch (error: any) {
      throw new Error();
    }
}

export async function addArticleToServer(article: Article) {
    try {
      const response = await fetch(BASE_API_URL + '/articles', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          articleId: article.articleId,
          title: article.title,
          context: article.context,
          author: article.author,
          date: article.date.toISOString(),
        category: article.category,
        }),
      });
      const result: any = await response.json();
      console.log('Article added with ID:', result.articleId);

      return {
        articleId: result.articleId,
        title: result.title,
        context: result.context,
        author: result.author,
        date: new Date(result.date),
        category: result.category,
      };
    } catch (error) {
      console.error('Failed to add Article:', error);
    }
  };

export async function updateArticleOnServer(article: Article) {
    const controller = new AbortController();
    const timeout = 2000;
    const timeoutId = setTimeout(() => controller.abort(), timeout);
    try {
    await fetch(`${BASE_API_URL}/articles/${article.articleId}`,  {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            articleId: article.articleId,
            title: article.title,
            context: article.context,
            author: article.author,
            date: article.date.toISOString(),
            category: article.category,
        }),
        signal: controller.signal,
      });
    } catch (error) {
      console.error('Failed to update Article:', error);
      throw new Error();
    }
};

export async function deleteArticleFromServer(articleId: number) {
    const controller = new AbortController();
    const timeout = 2000;
    const timeoutId = setTimeout(() => controller.abort(), timeout);

    try {
      await fetch(`${BASE_API_URL}/articles/${articleId}`, { method: 'DELETE', signal: controller.signal });
      console.log(`Article ${articleId} deleted`);
    } catch (error) {
      console.error('Failed to delete Article:', error);
      throw new Error();
    }
  };