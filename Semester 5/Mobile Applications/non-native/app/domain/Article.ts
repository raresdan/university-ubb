import { ArticleCategory } from "./ArticleCategory";

export interface Article {
    articleId: number;
    title: string;
    context: string;
    author: string;
    date: Date;
    category: ArticleCategory
}