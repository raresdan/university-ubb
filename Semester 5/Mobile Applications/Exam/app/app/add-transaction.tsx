import {
  View,
  Text,
  TextInput,
  Alert,
  StyleSheet,
  ActivityIndicator,
} from "react-native";
import React, { useState, useContext } from "react";
import { useRouter } from "expo-router";
import { RecordContext } from "@/contexts/RecordsContext";
import CustomButton from "@/components/CustomButton";

type Transaction = {
  id: number;
  date: string;
  amount: number;
  type: string;
  category: string;
  description: string;
};

const AddTransactionScreen = () => {
  const [date, setDate] = useState("");
  const [amount, setAmount] = useState("");
  const [type, setType] = useState("");
  const [category, setCategory] = useState("");
  const [description, setDescription] = useState("");

  const [showLoading, setShowLoading] = useState<boolean>(false);

  const recordsContext = useContext(RecordContext)!;
  const router = useRouter();

  const handleSubmit = async () => {
    if (!date || !amount || !type || !category || !description) {
      Alert.alert("Please fill in all fields");
      return;
    }

    const newTransaction: Transaction = {
      id: -1,
      date,
      amount: parseFloat(amount),
      type,
      category,
      description,
    };

    setShowLoading(true);
    try {
      await recordsContext.addRecord(newTransaction);
      Alert.alert("Transaction added successfully!");
      router.replace("/");
    } catch (error) {
      Alert.alert("Failed to add the transaction!");
    } finally {
      setShowLoading(false);
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Add New Transaction</Text>

      <TextInput
        style={styles.input}
        placeholder="Date (YYYY-MM-DD)"
        value={date}
        onChangeText={setDate}
      />
      <TextInput
        style={styles.input}
        placeholder="Amount"
        value={amount}
        keyboardType="numeric"
        onChangeText={setAmount}
      />
      <TextInput
        style={styles.input}
        placeholder="Type (e.g., income/expense)"
        value={type}
        onChangeText={setType}
      />
      <TextInput
        style={styles.input}
        placeholder="Category"
        value={category}
        onChangeText={setCategory}
      />
      <TextInput
        style={styles.input}
        placeholder="Description"
        value={description}
        onChangeText={setDescription}
      />

      <CustomButton text="Add Transaction" onPress={handleSubmit} />

      {showLoading && <ActivityIndicator size="large" />}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    justifyContent: "center",
    backgroundColor: "#E1E5DC",
  },
  header: {
    fontSize: 24,
    fontWeight: "bold",
    marginBottom: 20,
    textAlign: "center",
  },
  input: {
    height: 40,
    borderColor: "#ccc",
    borderWidth: 1,
    marginBottom: 15,
    paddingHorizontal: 10,
    borderRadius: 5,
  },
});

export default AddTransactionScreen;
