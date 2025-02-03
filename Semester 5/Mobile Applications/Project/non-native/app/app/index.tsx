import ArticleList from "@/components/ArticleList";
import { ArticleContext } from "@/context/ArticleContext";
import { useNavigation, useRouter } from "expo-router";
import { useContext, useEffect, useState } from "react";
import {
  Pressable,
  StyleSheet,
  Text,
  TextInput,
  View,
} from "react-native";
import { SafeAreaProvider, SafeAreaView } from "react-native-safe-area-context";

export default function Index() {
  const router = useRouter();
  const navigation = useNavigation();

  const articleContext = useContext(ArticleContext)!;

  const [searchQuery, setSearchQuery] = useState<string>("");
  const [filteredArticles, setFilteredArticles] = useState(
    articleContext.articles
  );

  useEffect(() => {
    setFilteredArticles(articleContext.articles);
  }, [articleContext.articles]);

  const handleSearch = (query: string) => {
    setSearchQuery(query);
    if (query.trim() === "") {
      setFilteredArticles(articleContext.articles);
    } else {
      const lowerCaseQuery = query.toLowerCase();
      const filtered = articleContext.articles.filter((article) =>
        article.title.toLowerCase().includes(lowerCaseQuery)
      );
      setFilteredArticles(filtered);
    }
  };

  return (
    <SafeAreaProvider>
      <SafeAreaView
        style={styles.container}
      >
        <Text style={styles.header}> Articles </Text>

        <View style={styles.searchRow}>
          <TextInput
            style={styles.input}
            placeholder="Search..."
            value={searchQuery}
            onChangeText={handleSearch}
          />
          <Pressable
            style={styles.addButton}
            onPress={() => router.navigate("/add_or_edit")}
          >
            <Text style={styles.addButtonText}>+</Text>
          </Pressable>
        </View>

        <ArticleList articles={filteredArticles} />

      </SafeAreaView>
    </SafeAreaProvider>
  );
}

const styles = StyleSheet.create({
  container: {
    paddingBottom: 16,
    flex: 1,
    justifyContent: "space-between",
    alignItems: "center",
    flexDirection: "column",
    margin: 16,
  },
  header: {
    alignContent: "center",
    fontWeight: "bold",
    fontSize: 18,
    marginBottom: 16,
  },
  searchRow: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    width: "100%",
    marginBottom: 16,
  },
  input: {
    height: 48,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    flex: 1, // Make input take available space
    paddingStart: 16,
    marginRight: 8, // Add spacing between input and button
  },
  addButton: {
    width: 48,
    height: 48,
    borderRadius: 24, // Ensures the button is circular
    backgroundColor: "#36454F", // Button color
    alignItems: "center",
    justifyContent: "center",
  },
  addButtonText: {
    color: "#FFFFFF", // White color for the "+"
    fontSize: 24,
    fontWeight: "bold",
  },
});