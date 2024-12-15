#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>
#include <vector>

std::vector<int> firstVector = {1, 2, 3, 4, 5};
std::vector<int> secondVector = {6, 7, 8, 9, 10};
std::vector<int> resultVector;


bool isReady = false, isDone = false;
std::mutex mtx;
std::condition_variable condVar;


void producer()
{
    for (int i = 0; i < firstVector.size(); i++)
    {
		std::unique_lock<std::mutex> lock(mtx);
		resultVector.push_back(firstVector[i] * secondVector[i]);
		isReady = true;
		if (i == firstVector.size() - 1)
		{
			isDone = true;
		}

		std::cout<< "Producer" << i << ": " << firstVector[i] << " * " << secondVector[i] << " = " << resultVector[i] << std::endl;
		condVar.notify_one();
	}
}

void consumer()
{
	int productSum = 0;
	for (int i = 0; i < firstVector.size(); i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
		condVar.wait(lock, [] { return isReady || isDone; });
		productSum += resultVector[i];
		std::cout << "Consumer" << i << ": " << productSum << std::endl;
		isReady = false;
	}
	std::cout << "Products Sum: " << productSum << std::endl;
}

int main()
{
	std::thread producerThread(producer);
	std::thread consumerThread(consumer);

	producerThread.join();
	consumerThread.join();

	return 0;
    
}

