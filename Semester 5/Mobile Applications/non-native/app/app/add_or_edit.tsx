import CustomButton from "@/components/CustomButton";
import { ArticleContext } from "@/context/ArticleContext";
import { Article } from "@/domain/Article";
import { ArticleCategory } from "@/domain/ArticleCategory";
import { useNavigation } from "expo-router";
import React, { useContext, useState } from "react";


import {
  Pressable,
  StyleSheet,
  Text,
  TextInput,
  View,
  Image,
  Alert,
} from "react-native";
import { SafeAreaProvider, SafeAreaView } from "react-native-safe-area-context";

import { Picker } from "@react-native-picker/picker";
import { showMessage } from "react-native-flash-message";

interface AddOrEditProps {
  article: Article | undefined;
}

export default function AddOrEdit({ article }: AddOrEditProps) {
  const navigation = useNavigation();
  const articlesContext = useContext(ArticleContext)!;

  const [title, setTitle] = useState<string>(article ? article.title : "");
  const [context, setContext] = useState<string>(
    article ? article.context : ""
  );
  const [author, setAuthor] = useState<string>(article ? article.author : "");
  const [category, setCategory] = useState<ArticleCategory>(
    article ? article.category : ArticleCategory.TECHNOLOGY
  );

  const validate = (article: Article) => {
    const errors: string[] = [];
    if (article.title.length < 3) {
      errors.push("Article title must be at least 3 characters long");
    }

    if (article.context.length < 10)
      errors.push("Article context must be at least 10 characters long");

    if (errors.length > 0)
      Alert.alert("Invalid values!", errors.join("\n"), [
        {
          text: "Ok",
        },
      ]);

    return errors.length > 0;
  };

  const onSave = () => {
    const articleToAdd: Article = {
      articleId: article ? article.articleId : 0,
      title: title,
      context: context,
      author: author,
      date: article ? article.date : new Date(),
      category: category,
    };

    if (validate(articleToAdd)) return;

    try{
      article ? articlesContext.updateArticle(articleToAdd) : articlesContext.addArticle(articleToAdd);
      navigation.goBack();
    } catch (error) {
      console.error("Error on add/update:", (error as Error).message);

      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  return (
    <SafeAreaProvider>
      <SafeAreaView
        style={{
          flex: 1,
          justifyContent: "center",
          alignItems: "center",
          margin: 16,
        }}
      >
        <Text style={styles.title}>{article ? "Edit Article" : "New Article"}</Text>

        <View style={styles.mainContent}>
          <View style={styles.fields}>
            <View>
              <Text style={{ marginBottom: 8, fontWeight: "bold" }}>Title</Text>
              <TextInput
                style={styles.titleInput}
                placeholder="Title"
                onChangeText={setTitle}
                value={title}
              />
            </View>

            <View>
              <Text style={{ marginBottom: 8, fontWeight: "bold" }}>Author</Text>
              <TextInput
                style={styles.authorInput}
                placeholder="Author"
                onChangeText={setAuthor}
                value={author}
              />
            </View>

            <View>
              <Text style={{ marginBottom: 8, fontWeight: "bold" }}>
                Description
              </Text>

              <TextInput
                multiline
                style={styles.contextInput}
                placeholder="Description"
                onChangeText={setContext}
                value={context}
                textAlignVertical="top"
              />
            </View>

            <View nativeID="category" style={styles.category}>
              <Text style={{ fontWeight: "bold" }}>Category</Text>

              <Picker
                onValueChange={setCategory}
                style={{
                  minWidth: 150,
                  marginRight: -16,
                }}
                selectedValue={category}
              >
                <Picker.Item label="Technology" value={ArticleCategory.TECHNOLOGY} />
                <Picker.Item label="Science" value={ArticleCategory.SCIENCE} />
                <Picker.Item label="Business" value={ArticleCategory.BUSINESS} />
                <Picker.Item label="Health" value={ArticleCategory.HEALTH} />
                <Picker.Item label="Sports" value={ArticleCategory.SPORTS} />
                <Picker.Item label="Education" value={ArticleCategory.EDUCATION} />
                <Picker.Item label="Travel" value={ArticleCategory.TRAVEL} />
                <Picker.Item label="Food" value={ArticleCategory.FOOD} />

              </Picker>
            </View>
          </View>

          <CustomButton
            onClick={() => {
              onSave();
            }}
            text="Post"
          />
        </View>
        
      </SafeAreaView>
    </SafeAreaProvider>
  );
}

const styles = StyleSheet.create({
  title: {
    fontWeight: "bold",
    fontSize: 18,
  },

  mainContent: {
    flex: 1,
    justifyContent: "space-between",
    width: "100%",
  },

  fields: {},

  titleInput: {
    height: 56,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    width: "100%",
    marginBottom: 16,
    paddingHorizontal: 16,
  },

  authorInput: {
    height: 56,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    width: "100%",
    marginBottom: 16,
    paddingHorizontal: 16,
  },

  contextInput: {
    height: 144,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    width: "100%",
    marginBottom: 16,
    padding: 16,
  },

  category: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    width: "auto",
  },
});