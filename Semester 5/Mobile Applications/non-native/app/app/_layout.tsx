import ArticleContextProvider from "@/context/ArticleContext";
import { Stack } from "expo-router";
import FlashMessage from "react-native-flash-message";

export default function RootLayout() {
  return(
    <ArticleContextProvider>
      <Stack>
        <Stack.Screen name="index" options={{ headerShown: false}} />
        <Stack.Screen name="add_or_edit" options={{ headerShown: false}} />
        <Stack.Screen name="edit/[articleId]" options={{ headerShown: false}} />
      </Stack>
      <FlashMessage position="top" />
    </ArticleContextProvider>
  );
}