export const IP = '10.0.2.2:2528';
const baseUrl = `http://${IP}`

function createAbortSignal() {
    const controller = new AbortController();
    const timeout = 2000;
    const timeoutId = setTimeout(() => controller.abort(), timeout);

    return {
        signal: controller.signal, 
        timeoutId: timeoutId
    };
}

export async function getDaysFromServer() {
    const {signal, timeoutId} = createAbortSignal();
    console.log('Fetching days from server.');

    try {
        const response = await fetch(baseUrl + '/dayData', {signal: signal});
        
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: string[] = await response.json();
        return data;
    }
    catch (error) {
        console.log(`Error on getDays: ${error}`);
        throw new Error();
    }
}


// GET /transactions
export async function getRecordsFromServer() {
    const {signal, timeoutId} = createAbortSignal();
    console.log(`Fetching all Transactions from server.`);

    try {
        const response = await fetch(baseUrl + `/transactions`, {signal: signal});
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: Transaction[] = await response.json();
        console.log("Transactions fetched: ", data);
        
        return data;
    }
    catch (error) {
        console.log(`Error on get records: ${error}`);
        throw new Error();
    }
}


// GET /transaction/:recordId
export async function getRecordDetailsFromServer(recordId: number) {
    const {signal, timeoutId} = createAbortSignal();
    console.log(`Fetching record details from server for: ${recordId}.`);

    try {
        const response = await fetch(baseUrl + `/transaction/${recordId}`, {signal: signal});
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: Transaction = await response.json();
        
        return data;
    }
    catch (error) {
        console.log(`Error on get records: ${error}`);
        throw new Error();
    }
}


// POST /transaction
export const postRecordToServer = async (record: Transaction): Promise<Transaction> => {
    console.log(`Posting record: ${record.id} to server.`);
  
    try {
      const response = await fetch(`http://${IP}/transaction`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(record),
      });
  
      if (!response.ok) {
        throw new Error(`Server responded with status: ${response.status}`);
      }
  
      const result = await response.json();
      console.log("Server response:", result);
  
      if (!result.id) {
        throw new Error("Server response missing 'id'");
      }
  
      return result;
    } catch (error: any) {
      console.error("Error in postRecordToServer:", error.message);
      throw error;
    }
  };
  


// DELETE /transaction/:id
export async function deleteRecordFromServer(recordId: number) {
    const {signal, timeoutId} = createAbortSignal();
    console.log(`Deleting record: ${recordId} from server.`);

    try {
        const response = await fetch(baseUrl + `/transaction/${recordId}`,
            {
                method: 'DELETE',
                headers: { 'Content-Type': 'application/json' },
                signal: signal
            });
        
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: Transaction = await response.json();
        
        return data;
    }
    catch (error) {
        console.log(`Error on delete record: ${error}`);
        throw new Error();
    }
}


// GET /allTransactions
export async function getAllRecordsFromServer() {
    const {signal, timeoutId} = createAbortSignal();
    console.log(`Fetching all Transactions from server.`);

    try {
        const response = await fetch(baseUrl + `/allTransactions`, {signal: signal});
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: Transaction[] = await response.json();
        console.log("Transactions fetched: ", data);
        
        return data;
    }
    catch (error) {
        console.log(`Error on get records: ${error}`);
        throw new Error();
    }
}


export async function updateRecordOnServer(recordId: number) {
    const {signal, timeoutId} = createAbortSignal();
    console.log(`Updating record: ${recordId} from server.`);

    try {
        const response = await fetch(baseUrl + `/enroll/${recordId}`,
            {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                signal: signal
            });
        
        if (!response.ok)
            throw new Error(`Response status not ok! Status: ${response.status}`);

        clearTimeout(timeoutId);

        const data: Transaction = await response.json();
        
        return data;
    }
    catch (error) {
        console.log(`Error on delete record: ${error}`);
        throw new Error();
    }
}


