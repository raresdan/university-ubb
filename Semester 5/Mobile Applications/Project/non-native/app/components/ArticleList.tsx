
import { Article } from "@/domain/Article";
import { FlatList } from "react-native";
import ArticleCard from "./ArticleCard";

interface ArticlesListProps {
  articles: Article[];
}

export default function ArticleList({ articles }: ArticlesListProps) {
  return (
    <FlatList
      style={{ width: "100%", marginTop: 16, paddingTop: 8 }}
      data={articles}
      renderItem={({ item }) => <ArticleCard article={item} />}
      keyExtractor={(item) => item.articleId.toString()}
      showsVerticalScrollIndicator={false}
    />
  );
}