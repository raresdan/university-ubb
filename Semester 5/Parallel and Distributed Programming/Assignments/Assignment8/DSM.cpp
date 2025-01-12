#include <mpi.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <mutex>
#include <chrono>
#include <cassert>


class Message {
    public:
        enum class Type { SUBSCRIBE, UPDATE, QUIT };

    private:
        std::unordered_map<std::string, std::string> fields;
        Type type;

    public:
        Message(Type type) : type(type) {}

        void setField(const std::string &key, const std::string &value) {
            fields[key] = value;
        }

        void setField(const std::string &key, int value) {
            fields[key] = std::to_string(value);
        }

        std::string getField(const std::string &key) const {
            return fields.at(key);
        }

        Type getType() const {
            return type;
        }

        std::string serialize() const {
            std::stringstream ss;
            ss << static_cast<int>(type);
            for (const auto &pair : fields) {
                ss << "|" << pair.first << "=" << pair.second;
            }
            return ss.str();
        }

        static Message deserialize(const std::string &data) {
            std::stringstream ss(data);
            int typeInt;
            ss >> typeInt;
            Type type = static_cast<Type>(typeInt);

            Message message(type);
            std::string field;
            while (std::getline(ss, field, '|')) {
                size_t pos = field.find('=');
                if (pos != std::string::npos) {
                    std::string key = field.substr(0, pos);
                    std::string value = field.substr(pos + 1);
                    message.setField(key, value);
                }
            }
            return message;
        }
    };

class DSM {
private:
    std::unordered_map<std::string, std::unordered_set<int>> subscribers;
    std::unordered_map<std::string, int> variables;
    std::mutex mtx;

public:
    DSM() {
        variables["a"] = 0;
        variables["b"] = 0;
        variables["c"] = 0;

        subscribers["a"] = {};
        subscribers["b"] = {};
        subscribers["c"] = {};
    }

    void updateVariable(const std::string &variable, int value) {
        setVariable(variable, value);

        Message message(Message::Type::UPDATE);
        message.setField("variable", variable);
        message.setField("value", value);

        sendToSubscribers(variable, message);
    }

    void setVariable(const std::string &variable, int value) {
        if (variables.find(variable) != variables.end()) {
            variables[variable] = value;
        }
    }

    void compareAndExchange(const std::string &variable, int oldValue, int newValue) {
        std::lock_guard<std::mutex> lock(mtx);
        if (variables[variable] == oldValue) {
            updateVariable(variable, newValue);
        }
    }

    void subscribe(const std::string &variable) {
        std::lock_guard<std::mutex> lock(mtx);
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (subscribers[variable].find(rank) == subscribers[variable].end()) {
            subscribers[variable].insert(rank);

            Message message(Message::Type::SUBSCRIBE);
            message.setField("variable", variable);
            message.setField("rank", rank);

            sendAll(message);
        }
    }

    void syncSubscription(const std::string &variable, int rank) {
        std::lock_guard<std::mutex> lock(mtx);
        subscribers[variable].insert(rank);
    }

    void receiveMessages() {
        char buffer[1024];
        MPI_Status status;
        while (true) {
            MPI_Recv(buffer, 1024, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            int count;
            MPI_Get_count(&status, MPI_CHAR, &count);
            buffer[count] = '\0';
            
            std::string message(buffer);
            // std::cout << "Received message: " << message << std::endl;
            
            Message msg = Message::deserialize(message);
            Message::Type messageType = msg.getType();

            if (messageType == Message::Type::QUIT) {
                int rank;
                MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                std::cout << "Recieved QUIT message (" << rank << " ended)" << std::endl;
                if (rank == 0) {
                    std::cout << "Final state: " << std::endl;
                    printState();
                }
                break;
            }

            if (messageType == Message::Type::UPDATE) {
                std::string variable = msg.getField("variable");
                int value = std::stoi(msg.getField("value"));
                std::cout << "Received UPDATE message (" << variable << " -> " << value << ")." << std::endl;
                setVariable(variable, value);
                printState();
            }

            if (messageType == Message::Type::SUBSCRIBE) {
                std::string variable = msg.getField("variable");
                int rank = std::stoi(msg.getField("rank"));
                std::cout << "Received SUBSCRIBE message (" << rank << " -> " << variable << ")." << std::endl;
                syncSubscription(variable, rank);
            }
        }
    }

    void sendToSubscribers(const std::string &variable, const Message &message) {
        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        for (int i = 0; i < size; ++i) {
            if (rank == i || subscribers[variable].find(i) == subscribers[variable].end()) {
                continue;
            }

            std::string serializedMessage = message.serialize();
            // std::cout << "Sending message to rank " << i << ": " << serializedMessage << std::endl;
            MPI_Send(serializedMessage.c_str(), serializedMessage.size(), MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }

    void sendAll(const Message &message) {
        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        for (int i = 0; i < size; ++i) {
            if (rank == i && message.getType() != Message::Type::QUIT) {
                continue;
            }

            std::string serializedMessage = message.serialize();
            MPI_Send(serializedMessage.c_str(), serializedMessage.size(), MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }

    void close() {
        sendAll(Message(Message::Type::QUIT));
    }

    void printState() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "DSM State: ";
        for (const auto &pair : variables) {
            std::cout << pair.first << "=" << pair.second << " ";
        }
        std::cout << std::endl;
    }
};


void master(DSM &dsm) {
    std::thread listener([&dsm]() {
        dsm.receiveMessages();
    });

    dsm.subscribe("a");
    dsm.subscribe("b");
    dsm.subscribe("c");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    dsm.compareAndExchange("a", 0, 33);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    dsm.compareAndExchange("c", 0, 15);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    dsm.updateVariable("b", 50);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    dsm.close();

    listener.join();
}


void worker(DSM &dsm) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::thread listener([&dsm]() {
        dsm.receiveMessages();
    });

    if (rank == 1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dsm.subscribe("a");
        dsm.subscribe("c");

        std::this_thread::sleep_for(std::chrono::seconds(1));
        dsm.compareAndExchange("a", 33, 420);
        dsm.compareAndExchange("c", 15, 32);
    } else {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        dsm.subscribe("b");

        std::this_thread::sleep_for(std::chrono::seconds(2));
        dsm.compareAndExchange("b", 50, 100);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    listener.join();
}


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    DSM dsm;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        master(dsm);
    } else {
        worker(dsm);
    }

    MPI_Finalize();
    return 0;
}



// Run with:
// mpic++ DSM.cpp -o DSM
// mpirun -np <num_processes> ./DSM