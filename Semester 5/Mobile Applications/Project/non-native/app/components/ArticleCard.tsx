import { Alert, Image, Pressable, StyleSheet, Text, View } from "react-native";
import { useContext, useState } from "react";
import { useRouter } from "expo-router";
import { Article } from "@/domain/Article";
import { ArticleContext } from "@/context/ArticleContext";
import { showMessage } from "react-native-flash-message";


type ArticleCardProps = {
  article: Article;
};

const maxTextLength = 55;
const maxContextLength = 100;

function getTitle(article: Article): string {
  return article.title.length > maxTextLength
    ? article.title.slice(0, maxTextLength) + "..."
    : article.title;
}

function getAuthor(article: Article): string {
  return article.author;
}

function getContext(article: Article): string {
  return article.context.length > maxContextLength
    ? article.context.slice(0, maxContextLength) + "..."
    : article.context;
}

function getCategory(article: Article): string {
  return article.category;
}

function getDate(article: Article): string {
  return article.date.toDateString();
}


export default function ArticleCard({ article }: ArticleCardProps) {
  const articleContext = useContext(ArticleContext)!;
  const router = useRouter();

  const deleteArticle = () => {
    try{
      articleContext.deleteArticle(article.articleId);
    } catch (error) {
      console.error(error);

      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  }

  const createConfirmDialog = () => {
    Alert.alert(
      "Delete confirmation",
      "Are you sure you want to remove this article?",
      [
        {
          text: "No",
          style: "cancel",
        },

        {
          text: "Yes",
          onPress: deleteArticle,
        },
      ]
    );
  };

  return (
    <View style={styles.articleCard}>

      <Text style={styles.title}>{getTitle(article)}</Text>
      <View style={styles.detailsContainer}>
        <Text style={styles.details}>{getAuthor(article)}</Text>
        <Text style={styles.details}>{getDate(article)}</Text>
      </View>
      <View style={styles.categoryContainer}>
        <Text style={styles.category}>{getCategory(article)}</Text>
      </View>
      <Text style={styles.context}>{getContext(article)}</Text>

      <View style={styles.actions}>
        <Pressable
          onPress={() => {
            console.log(article.articleId);

            router.navigate(`./edit/${article.articleId}`);
          }}
          style={styles.editButton}
        >
          <Text style={styles.buttonText}>Edit</Text>
        </Pressable>

        <Pressable onPress={createConfirmDialog}>
          <Image source={require("../assets/images/trash.png")}/>
        </Pressable>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  articleCard: {
    backgroundColor: "#F7F8FA",
    borderRadius: 8,
    padding: 16,
    marginBottom: 16,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 2,
  },
  title: {
    fontSize: 18,
    fontWeight: "bold",
    marginBottom: 8,
    color: "#212121",
  },
  detailsContainer: {
    flexDirection: "row",
    justifyContent: "space-between",
    marginBottom: 8,
  },
  details: {
    fontSize: 14,
    color: "#757575",
    marginBottom: 8,
  },
  categoryContainer: {
    backgroundColor: "#E0E0E0",
    borderRadius: 16,
    paddingHorizontal: 12,
    paddingVertical: 4,
    alignSelf: "flex-start",
    marginBottom: 8,
  },
  category: {
    fontSize: 12,
    fontWeight: "600",
    color: "#424242",
  },
  context: {
    fontSize: 14,
    color: "#616161",
    marginBottom: 16,
  },
  actions: {
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
  },
  editButton: {
    backgroundColor: "#36454F",
    borderRadius: 8,
    paddingVertical: 8,
    paddingHorizontal: 16,
  },
  buttonText: {
    color: "#FFFFFF",
    fontWeight: "bold",
    fontSize: 14,
  }
});