import {
  deleteRecordFromServer,
  getDaysFromServer,
  getRecordDetailsFromServer,
  getRecordsFromServer,
  getAllRecordsFromServer,
  IP,
  postRecordToServer,
} from "@/repository/NetworkRepository";
import { SplashScreen } from "expo-router";
import { createContext, useEffect, useState } from "react";
import { showMessage } from "react-native-flash-message";
import * as SQLite from "expo-sqlite";
import {
  addFetchedRecordDb,
  addRecordDb,
  addToSyncQueue,
  clearLocalDb,
  clearSyncQueue,
  createTable,
  deleteRecordDb,
  getAllFetchedRecordsDb,
  getAllRecordsDb,
  getSyncQueue,
  removeFromSyncQueue,
  updateRecordDb,
} from "@/repository/SQLRepository";

type RecordContextType = {
  records: Transaction[];
  addRecord: (record: Transaction) => Promise<void>;
  updateRecord: (record: Transaction) => Promise<void>;
  deleteRecord: (recordId: number) => Promise<void>;
  getRecords: () => Promise<void>;
  getRecordDetails?: (recordId: number) => Promise<Transaction | null>;
  getAllRecordsFromServer?: () => Promise<void>;
  isLoaded?: boolean;
  retryFetch?: () => Promise<void>;
};

export const RecordContext = createContext<RecordContextType | null>(null);

export default function RecordContextProvider({ children }: any) {
  const [records, setRecords] = useState<Transaction[]>([]);
  const [isLoaded, setIsLoaded] = useState<boolean>(false);

  const [retrievedFor, setRetrievedFor] = useState<number[]>([]);
  const [dbConnection, setDbConnection] = useState<SQLite.SQLiteDatabase>();

  const addRecord = async (record: Transaction) => {
    try {
      const receivedRecord = await postRecordToServer(record);
      await addRecordDb(dbConnection!, receivedRecord);

      setRecords((prevRecords) => [...prevRecords, receivedRecord]);
    } catch (error) {
      console.log("failed to save on server... fallback to local sync queue");
      let maxId =
        Math.max.apply(
          Math,
          records.map((transaction) => transaction.id)
        ) + 1;

      const receivedRecord = { ...record, id: maxId };

      await addRecordDb(dbConnection!, receivedRecord);

      await addToSyncQueue(
        dbConnection!,
        maxId,
        "ADD",
        JSON.stringify(receivedRecord)
      );

      setRecords((prevRecords) => [...prevRecords, receivedRecord]);

      showMessage({
        message: "Failed to post record!",
        type: "warning",
        duration: 2000,
      });
    }
  };

  const updateRecord = async (record: Transaction) => {
    try {
      // Update the record in the database
      await updateRecordDb(dbConnection!, record);
      console.log("received: ");
      console.log(record);

      // Update the record in the local state
      setRecords((prevRecords) =>
        prevRecords.map((transaction) => (transaction.id == record.id ? record : transaction))
      );
    } catch (error) {
      console.error("Error updating record:", error);
      showMessage({
        message: "Failed to update record",
        type: "warning",
        duration: 2000,
      });
    }
  };

  const deleteRecord = async (recordId: number) => {
    try {
      await deleteRecordFromServer(recordId);

      setRecords((prevRecords) =>
        prevRecords.filter((record) => record.id != recordId)
      );
    } catch (error) {
      showMessage({
        message: "Failed to delete record!",
        type: "warning",
        duration: 2000,
      });
    }
  };

  const getRecords = async () => {
    try {
      const result = await getRecordsFromServer();

      setRecords((prevRecords) => [...prevRecords, ...result]);
      setIsLoaded(true);
      for (let record of result) await addRecordDb(dbConnection!, record);
    } catch (error) {
      showMessage({
        message: "Failed to get records!",
        type: "warning",
        duration: 2000,
      });
    }
  };

  const getRecordDetails = async (recordId: number) => {
    try {
      if (retrievedFor.find((record) => record == recordId))
        return records.find((record) => record.id == recordId)!;

      const result = await getRecordDetailsFromServer(recordId);
      await addFetchedRecordDb(dbConnection!, recordId);
      retrievedFor.push(recordId);

      return result;
    } catch (error) {
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });

      return null;
    }
  };

  const getAllRecords = async () => {
    try {
      const result = await getAllRecordsFromServer(); // Fetch all transactions from the server
  
      console.log("Fetched all records from server:", result);
  
      // Directly update the state with server data
      setRecords(result);
      setIsLoaded(true);
  
      showMessage({
        message: "All records successfully fetched from the server!",
        type: "success",
        duration: 2000,
      });
    } catch (error) {
      console.error("Failed to fetch all records from the server:", error);
  
      showMessage({
        message: "Failed to fetch all records from the server!",
        type: "warning",
        duration: 2000,
      });
    }
  };
  

  async function loadRecordsFromDb(dbConnection: SQLite.SQLiteDatabase) {
    try {
      const records = await getAllRecordsDb(dbConnection);
      const fetchedRecords = await getAllFetchedRecordsDb(dbConnection);
      
      setRecords(records);
      setRetrievedFor([...new Set(fetchedRecords.map((entry) => entry.id))]);

      setIsLoaded(true);
      return records.length > 0;
    } catch (error) {
      showMessage({
        message: "Failed to load records!",
        type: "warning",
        duration: 2000,
      });
    }
  }

  const setupWebSocket = () => {
    const socket = new WebSocket(`ws://${IP}`);

    socket.onopen = () => {
      console.log("WebSocket connection established");
    };

    socket.onmessage = async (event) => {
      const receivedRecord: Transaction = JSON.parse(event.data);

      console.log(receivedRecord.id);

      // setRecords((prevRecords) => {
      //   if (
      //     prevRecords.find((record) => record.id == receivedRecord.id) !=
      //     undefined
      //   )
      //     return prevRecords;

      //   return [...prevRecords, receivedRecord];
      // });

      // const formattedMessage = `New Project From team: ${receivedRecord.team} with ${receivedRecord.members} members, status: ${receivedRecord.status}. Description: ${receivedRecord.details}`;
      const formattedMessage = ""
      showMessage({
        message: formattedMessage,
        duration: 3000,
        type: "info",
      });
    };

    socket.onclose = () => console.log("WebSocket connection closed");
  };

  const syncItems = async () => {
    console.log("SyncItems called at", new Date().toISOString());

    const syncQueue = await getSyncQueue(dbConnection!);
    console.log(syncQueue);
    if (syncQueue.length == 0) return;

    for (let item of syncQueue) {
      console.log(`syncing: ${item}`);

      const { id, recordId, syncAction, payload } = item;

      const oldRecord = JSON.parse(payload);

      try {
        const receivedRecord = await postRecordToServer(oldRecord);
        await removeFromSyncQueue(dbConnection!, id);
        await deleteRecordDb(dbConnection!, recordId);
        await addRecordDb(dbConnection!, receivedRecord);
        // remove temp entity and add the server one
        setRecords((prevRecords) => [
          ...prevRecords.filter((record) => record.id != oldRecord.id),
          receivedRecord,
        ]);
      } catch (error) {}
    }
  };

  useEffect(() => {
    SplashScreen.preventAutoHideAsync();

    const connection = SQLite.openDatabaseSync("tasks.db");

    // clearSyncQueue(connection);
    // clearLocalDb(connection);

    async function loadData() {
      const result = await loadRecordsFromDb(connection);

      if (result) return;

      await getRecords();
    }

    loadData();

    setDbConnection(connection);
    createTable(connection);

    setupWebSocket();

    setInterval(() => syncItems(), 5000);
  }, []);

  return (
    <RecordContext.Provider
      value={{
        records: records,
        addRecord: addRecord,
        updateRecord: updateRecord,
        deleteRecord: deleteRecord,
        getRecords: getRecords,
        getAllRecordsFromServer: getAllRecords,
        isLoaded: isLoaded,
        retryFetch: getRecords,
        getRecordDetails: getRecordDetails,
      }}
    >
      {children}
    </RecordContext.Provider>
  );
}
