import CustomButton from "@/components/CustomButton";
import TransactionCard from "@/components/TransactionCard";
import ProjectCard from "@/components/TransactionCard";
import { RecordContext } from "@/contexts/RecordsContext";
import { useRouter } from "expo-router";
import { useContext, useState } from "react";
import {
  ActivityIndicator,
  ScrollView,
  StyleSheet,
  Text,
  View,
} from "react-native";
import { SafeAreaView } from "react-native-safe-area-context";

export default function Index() {
  const recordsContext = useContext(RecordContext)!;
  const [showLoading, setShowLoading] = useState<boolean>(false);

  const router = useRouter();

  return (
    <SafeAreaView style={styles.main}>
      <Text style={styles.title}>My App</Text>

      {recordsContext.isLoaded == true ? (
        <ScrollView style={styles.itemsContainer}>
          {recordsContext.records.map((record, key) => (
            <TransactionCard transaction={record} key={key} />
          ))}
        </ScrollView>
      ) : (
        <View>
          <Text>Dates load failed!</Text>

          <CustomButton
            text="Retry"
            onPress={() => {
              setShowLoading(true);
              if (recordsContext.retryFetch !== undefined)
                recordsContext
                  .retryFetch()
                  .finally(() => setShowLoading(false));
            }}
          />
        </View>
      )}

      {showLoading && <ActivityIndicator />}

      <View style={styles.buttonContainer}>
        <CustomButton
          text={" + "}
          onPress={() => router.navigate("/add-transaction")}
        />
        <CustomButton
          text={"Monthly Spendings"}
          onPress={() => router.push("/analytics")}
        />
        <CustomButton
          text={"Top 3"}
          onPress={() => router.push("/team-member")}
        />
      </View>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  main: {
    flex: 1,
    padding: 16,
    backgroundColor: "#E1E5DC", // Optional background color for better contrast
  },

  title: {
    fontWeight: "bold",
    fontSize: 24,
    textAlign: "center",
    marginBottom: 16,
  },

  itemsContainer: {
    flex: 1, // Allow the ScrollView to take up available space
    width: "100%", // Make the container full-width
  },

  buttonContainer: {
    flexDirection: "row", // Align buttons horizontally
    justifyContent: "space-around", // Evenly distribute buttons
    alignItems: "center", // Align buttons vertically
    marginTop: 16,
  },

  failContainer: {
    marginTop: 32,
    alignItems: "center",
  },
});
