#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <unordered_map>

using namespace std;

typedef struct {
    int serialNumber;
    int amount;
    int sourceId;
    int destinationId;
}transferOperation;

typedef struct {
    int accountId;
    int initialBalance;
    int currentBalance;
    mutex* mtx;
    vector<transferOperation> operationsLog;
}Account;

const string FILE_NAME = "input.txt";

int currentSerialNumber = 0;
int numberOfThreads;
unordered_map<int, Account> accounts;
vector<int> accountIds;
vector<transferOperation> operations;

bool checkPassed = true;
mutex checkMtx;

void readAccountsFromFile(string filePath) {
    // Read accounts from file and store them in a map
	ifstream file(filePath);
    if (!file.is_open()) {
		cout << "File cannot be opened!" << endl;
		return;
	}

    while (file) {
        int accountId, balance;
        file >> accountId >> balance;

        if (!file.eof()) {
			Account account;
            account.accountId = accountId;
            account.initialBalance = balance;
            account.currentBalance = balance;
            account.mtx = new mutex();
            accounts[accountId] = account;
            accountIds.push_back(accountId);
		}
    }
	file.close();
}

int generateRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

int getRandomAccountId() {
	return accountIds[generateRandomNumber(0, accountIds.size() - 1)];
}

int getRandomAmount() {
	return generateRandomNumber(1, 100);
}

void generateRandomOperations(int size) {
    // Generate random operations with random source and destination accounts and random amounts between 1 and 100 
    for (int i = 0; i < size; i++) {
		transferOperation operation;
		operation.amount = getRandomAmount();
		operation.sourceId = getRandomAccountId();
		operation.destinationId = getRandomAccountId();
        while (operation.sourceId == operation.destinationId)
        {
            operation.destinationId = getRandomAccountId();
        }
        operation.serialNumber = ++currentSerialNumber;
		operations.push_back(operation);
	}
}

void performConsistencyCheck() {
    // Check if the sum of all operations is equal to the current balance of each account
    for (auto& acc : accounts) {
        acc.second.mtx->lock();

        Account& account = acc.second;
        int totalBalance = account.initialBalance;
        for (transferOperation& operation : account.operationsLog) {
            if (operation.sourceId == account.accountId) {
				totalBalance -= operation.amount;
			}
            else if (operation.destinationId == account.accountId) {
				totalBalance += operation.amount;
			}
        }
        if (totalBalance != account.currentBalance) {
            checkMtx.lock();
			checkPassed = false;
			checkMtx.unlock();
		}

		acc.second.mtx->unlock();
	}
}

void threadManager(int threadIdentifier) {
    // Divide the operations between threads
    int batchSize = operations.size() / numberOfThreads;
    int start = threadIdentifier * batchSize;
    int end = (threadIdentifier == numberOfThreads - 1) ? operations.size() : start + batchSize;
    for (int i = start; i < end; i++) {
        // Update first account balance
        accounts[operations[i].sourceId].mtx->lock();
        if (accounts[operations[i].sourceId].currentBalance - operations[i].amount < 0)
        {
            accounts[operations[i].sourceId].mtx->unlock();
            continue;
        }
        accounts[operations[i].sourceId].currentBalance -= operations[i].amount;
        accounts[operations[i].sourceId].operationsLog.push_back(operations[i]);
        accounts[operations[i].sourceId].mtx->unlock();

        // Update second account balance
        accounts[operations[i].destinationId].mtx->lock();
        accounts[operations[i].destinationId].currentBalance += operations[i].amount;
        accounts[operations[i].destinationId].operationsLog.push_back(operations[i]);
        accounts[operations[i].destinationId].mtx->unlock();

        if (i % 10 == 0)
        {
            performConsistencyCheck();
        }
        
    }
}

int main()
{
    numberOfThreads = 8;
    int operationsCount = 100000;

    readAccountsFromFile(FILE_NAME);
    generateRandomOperations(operationsCount);

    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads.push_back(thread(threadManager, i));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    performConsistencyCheck();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    for (auto& entry : accounts)
    {
        cout << "Account: " << entry.first << ", Balance: " << entry.second.currentBalance << endl;
        cout << "Operations performed: " << entry.second.operationsLog.size() << endl;
        delete entry.second.mtx;
    }

    if (checkPassed)
    {
        cout << endl << "Consistency checks passed!" << endl;
    }
    else
    {
        cout << "Consistency check did not pass!" << endl;
    }

    cout << "Execution Time: " << duration.count() << " seconds" << endl;

    return 0;
}

