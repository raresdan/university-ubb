import React, { useContext, useEffect, useState } from "react";
import {
  SafeAreaView,
  Text,
  StyleSheet,
  ActivityIndicator,
  View,
  ScrollView,
} from "react-native";
import { RecordContext } from "@/contexts/RecordsContext";
import { useLocalSearchParams } from "expo-router";

export default function TransactionDetails() {
  const recordsContext = useContext(RecordContext)!;
  const { transactionId } = useLocalSearchParams(); // Assume `transactionId` is passed as a route parameter
  const [transactionDetails, setTransactionDetails] = useState<Transaction | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchDetails = async () => {
      if (transactionId) {
        const details = recordsContext.getRecordDetails
          ? await recordsContext.getRecordDetails(Number(transactionId))
          : null;

        setTransactionDetails(details);
      }
      setLoading(false);
    };

    fetchDetails();
  }, [transactionId]);

  if (loading) {
    return (
      <SafeAreaView style={styles.main}>
        <ActivityIndicator size="large" color="#4CAF50" />
      </SafeAreaView>
    );
  }

  if (!transactionDetails) {
    return (
      <SafeAreaView style={styles.main}>
        <Text style={styles.errorText}>Failed to load transaction details.</Text>
      </SafeAreaView>
    );
  }

  return (
    <SafeAreaView style={styles.main}>
      <ScrollView contentContainerStyle={styles.scrollContainer}>
        <Text style={styles.title}>Transaction Details</Text>
        <View style={styles.card}>
          <DetailRow label="ID" value={transactionDetails.id} />
          <DetailRow label="Date" value={transactionDetails.date} />
          <DetailRow label="Amount" value={`$${transactionDetails.amount.toFixed(2)}`} />
          <DetailRow label="Type" value={transactionDetails.type} />
          <DetailRow label="Category" value={transactionDetails.category} />
          <DetailRow label="Description" value={transactionDetails.description} />
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const DetailRow = ({ label, value }: { label: string; value: string | number }) => (
  <View style={styles.detailRow}>
    <Text style={styles.label}>{label}:</Text>
    <Text style={styles.value}>{value}</Text>
  </View>
);

const styles = StyleSheet.create({
  main: {
    flex: 1,
    padding: 16,
    backgroundColor: "#f0f4f8",
  },
  scrollContainer: {
    alignItems: "center",
  },
  title: {
    fontSize: 32,
    fontWeight: "bold",
    color: "#333",
    marginBottom: 24,
    textAlign: "center",
  },
  card: {
    width: "100%",
    backgroundColor: "#fff",
    borderRadius: 12,
    padding: 20,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.1,
    shadowRadius: 6,
    elevation: 4,
    borderColor: "#ddd",
    borderWidth: 1,
  },
  detailRow: {
    flexDirection: "row",
    justifyContent: "space-between",
    marginBottom: 12,
    borderBottomWidth: 1,
    borderBottomColor: "#f0f0f0",
    paddingBottom: 8,
  },
  label: {
    fontSize: 18,
    fontWeight: "600",
    color: "#555",
  },
  value: {
    fontSize: 18,
    color: "#333",
    textAlign: "right",
    flex: 1,
    marginLeft: 10,
  },
  errorText: {
    fontSize: 18,
    color: "red",
    textAlign: "center",
  },
});
