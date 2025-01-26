import { ArticleContext } from "@/context/ArticleContext";
import { useLocalSearchParams } from "expo-router";
import { useContext } from "react";
import AddOrEdit from "../add_or_edit";

export default function erdit() {
    const articlesContext = useContext(ArticleContext)!;
    const { articleId } = useLocalSearchParams();
    const article = articlesContext.getArticle(Number(articleId));
    if (article === undefined) return;
    return <AddOrEdit article={article} />;
}