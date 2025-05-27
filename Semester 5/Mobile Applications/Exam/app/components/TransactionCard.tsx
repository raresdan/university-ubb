import React, { useContext } from "react";
import { View, Text, StyleSheet, Pressable, Button } from "react-native";
import { useRouter } from "expo-router";
import { RecordContext } from "@/contexts/RecordsContext";

type TransactionCardProps = {
  transaction: Transaction;
};

const TransactionCard = ({ transaction }: TransactionCardProps) => {
  const router = useRouter();
  const recordsContext = useContext(RecordContext);

  const handleDelete = async () => {
    if (recordsContext?.deleteRecord) {
      try {
        await recordsContext.deleteRecord(transaction.id);
      } catch (error) {
        console.error("Failed to delete record:", error);
      }
    }
  };

  return (
    <View style={styles.card}>
      <Pressable
        onPress={() => router.push(`./details/${transaction.id}`)}
        style={({ pressed }) => [
          styles.content,
          pressed && styles.cardPressed, // Add visual feedback on press
        ]}
      >
        <View>
          <Text style={styles.date}>{transaction.date}</Text>
          <Text style={styles.amount}>Amount: ${transaction.amount.toFixed(2)}</Text>
          <Text style={styles.type}>Type: {transaction.type}</Text>
          <Text style={styles.category}>Category: {transaction.category}</Text>
          <Text style={styles.description}>{transaction.description}</Text>
          <Text style={styles.id}>ID: {transaction.id}</Text>
        </View>
      </Pressable>
      <Button
        title="Delete"
        onPress={() => handleDelete()}
        color="#FF4C4C" // Red button for delete
      />
    </View>
  );
};

const styles = StyleSheet.create({
  card: {
    backgroundColor: "#F6F7F2",
    padding: 15,
    marginVertical: 10,
    borderRadius: 12,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.2,
    shadowRadius: 4,
    elevation: 5,
    borderColor: "#ddd",
    borderWidth: 1,
  },
  cardPressed: {
    opacity: 0.85, // Slight dimming effect on press
  },
  content: {
    alignItems: "flex-start",
  },
  date: {
    fontSize: 16,
    fontWeight: "bold",
    color: "#333",
    marginBottom: 5,
  },
  amount: {
    fontSize: 16,
    color: "#4CAF50", // Green color for amount
    marginBottom: 5,
  },
  type: {
    fontSize: 14,
    color: "#888",
    marginBottom: 5,
  },
  category: {
    fontSize: 14,
    color: "#666",
    marginBottom: 5,
  },
  description: {
    fontSize: 14,
    color: "#444",
    marginBottom: 5,
  },
  id: {
    fontSize: 12,
    color: "#aaa",
  },
});

export default TransactionCard;
