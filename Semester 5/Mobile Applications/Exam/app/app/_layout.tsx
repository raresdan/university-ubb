import React from "react";
import NetworkContextProvider from "@/contexts/NetworkContext";
import RecordContextProvider from "@/contexts/RecordsContext";
import { Stack } from "expo-router";
import FlashMessage from "react-native-flash-message";

export default function RootLayout() {
  return (
    <>
      <NetworkContextProvider>
        <RecordContextProvider>
          <Stack>
            <Stack.Screen name="index" options={{ headerShown: false }} />
            <Stack.Screen
              name="details/[transactionId]"
              options={{ headerShown: false }}
            />
            <Stack.Screen name="add-transaction" options={{ headerShown: false }} />
            <Stack.Screen name="team-member" options={{ headerShown: false }} />
            <Stack.Screen name="analytics" options={{ headerShown: false }} />
          </Stack>
        </RecordContextProvider>
      </NetworkContextProvider>
      <FlashMessage position="top" />
    </>
  );
}
