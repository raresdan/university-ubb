import React, { useEffect, useState, useContext } from "react";
import {
  View,
  Text,
  FlatList,
  StyleSheet,
  ActivityIndicator,
} from "react-native";
import { RecordContext } from "@/contexts/RecordsContext";

type MonthlySpending = {
  month: string;
  total: number;
};

const MonthlySpendingScreen = () => {
  const recordsContext = useContext(RecordContext);
  const [monthlySpending, setMonthlySpending] = useState<MonthlySpending[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);

  const fetchAndAnalyzeSpending = async () => {
    setIsLoading(true);
    try {
      if (recordsContext?.getAllRecordsFromServer) {
        await recordsContext.getAllRecordsFromServer();
      }

      const transactions = recordsContext?.records || [];

      // Group transactions by month and calculate total spending
      const spendingByMonth: { [key: string]: number } = {};
      transactions.forEach((transaction) => {
          const date = new Date(transaction.date);
          const month = `${date.getFullYear()}-${(date.getMonth() + 1)
            .toString()
            .padStart(2, "0")}`; // Format: YYYY-MM

          spendingByMonth[month] = (spendingByMonth[month] || 0) + transaction.amount;
      });

      // Convert to array and sort by total spending in descending order
      const sortedSpending = Object.entries(spendingByMonth)
        .map(([month, total]) => ({ month, total }))
        .sort((a, b) => b.total - a.total);

      setMonthlySpending(sortedSpending);
    } catch (error) {
      console.error("Failed to fetch or analyze spending:", error);
    } finally {
      setIsLoading(false);
    }
  };

  useEffect(() => {
    fetchAndAnalyzeSpending();
  }, []);

  const renderItem = ({ item }: { item: MonthlySpending }) => (
    <View style={styles.spendingCard}>
      <Text style={styles.month}>{item.month}</Text>
      <Text style={styles.total}>{`Total: $${item.total.toFixed(2)}`}</Text>
    </View>
  );

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Monthly Spending Analysis</Text>
      {isLoading ? (
        <ActivityIndicator size="large" />
      ) : monthlySpending.length > 0 ? (
        <FlatList
          data={monthlySpending}
          renderItem={renderItem}
          keyExtractor={(item) => item.month}
        />
      ) : (
        <Text style={styles.noDataMessage}>No spending data available</Text>
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
  spendingCard: {
    backgroundColor: "#fff",
    padding: 15,
    marginBottom: 10,
    borderRadius: 8,
    shadowColor: "#000",
    shadowOpacity: 0.1,
    shadowRadius: 5,
    shadowOffset: { width: 0, height: 2 },
  },
  month: {
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

export default MonthlySpendingScreen;
