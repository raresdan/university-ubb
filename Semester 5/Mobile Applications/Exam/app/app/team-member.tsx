import React, { useEffect, useState, useContext } from "react";
import {
  View,
  Text,
  FlatList,
  StyleSheet,
  ActivityIndicator,
} from "react-native";
import { RecordContext } from "@/contexts/RecordsContext";

type CategorySpending = {
  category: string;
  total: number;
};

const TopSpendingCategoriesScreen = () => {
  const recordsContext = useContext(RecordContext);
  const [categorySpending, setCategorySpending] = useState<CategorySpending[]>(
    []
  );
  const [isLoading, setIsLoading] = useState<boolean>(false);

  const fetchAndAnalyzeCategories = async () => {
    setIsLoading(true);
    try {
      if (recordsContext?.getAllRecordsFromServer) {
        await recordsContext.getAllRecordsFromServer();
      }

      const transactions = recordsContext?.records || [];

      // Group transactions by category and calculate total spending
      const spendingByCategory: { [key: string]: number } = {};
      transactions.forEach((transaction) => {
        if (
          transaction.type === "expense" &&
          !isNaN(transaction.amount) &&
          transaction.category
        ) {
          spendingByCategory[transaction.category] =
            (spendingByCategory[transaction.category] || 0) +
            transaction.amount;
        }
      });

      // Convert to array and sort by total spending in descending order
      const sortedSpending = Object.entries(spendingByCategory)
        .map(([category, total]) => ({ category, total }))
        .sort((a, b) => b.total - a.total)
        .slice(0, 3); // Get the top 3 categories

      setCategorySpending(sortedSpending);
    } catch (error) {
      console.error("Failed to fetch or analyze category spending:", error);
    } finally {
      setIsLoading(false);
    }
  };

  useEffect(() => {
    fetchAndAnalyzeCategories();
  }, []);

  const renderItem = ({ item }: { item: CategorySpending }) => (
    <View style={styles.categoryCard}>
      <Text style={styles.category}>{item.category}</Text>
      <Text style={styles.total}>{`Total: $${item.total.toFixed(2)}`}</Text>
    </View>
  );

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Top 3 Spending Categories</Text>
      {isLoading ? (
        <ActivityIndicator size="large" />
      ) : categorySpending.length > 0 ? (
        <FlatList
          data={categorySpending}
          renderItem={renderItem}
          keyExtractor={(item) => item.category}
        />
      ) : (
        <Text style={styles.noDataMessage}>
          No spending data available by category
        </Text>
      )}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    backgroundColor: "#E1E5DC",
  },
  header: {
    fontSize: 24,
    fontWeight: "bold",
    marginBottom: 20,
    textAlign: "center",
  },
  categoryCard: {
    backgroundColor: "#fff",
    padding: 15,
    marginBottom: 10,
    borderRadius: 8,
    shadowColor: "#000",
    shadowOpacity: 0.1,
    shadowRadius: 5,
    shadowOffset: { width: 0, height: 2 },
  },
  category: {
    fontSize: 18,
    fontWeight: "bold",
  },
  total: {
    fontSize: 16,
    color: "#4CAF50", // Green for spending
    marginTop: 5,
  },
  noDataMessage: {
    textAlign: "center",
    fontSize: 18,
    color: "#888",
    marginTop: 20,
  },
});

export default TopSpendingCategoriesScreen;
