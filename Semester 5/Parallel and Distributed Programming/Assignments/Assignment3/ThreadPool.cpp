#include <iostream>
#include <future>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <ctime>
#include <cstdlib>


class ThreadPool
{
	public:
		ThreadPool(size_t numberOfThreads);
		~ThreadPool();
		template<class F>
		void enqueue(F&& function);
	private:
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> tasks;
		std::mutex queueMutex;
		std::condition_variable condition;
		bool stop;

		void workerThread();
};

ThreadPool::ThreadPool(size_t numberOfThreads) : stop(false)
{
	for (size_t i = 0; i < numberOfThreads; ++i)
	{
		threads.emplace_back(&ThreadPool::workerThread, this);
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread& thread : threads)
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}
}


template<class F>
void ThreadPool::enqueue(F&& function)
{
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		tasks.emplace(std::forward<F>(function));
	}
	condition.notify_one();
}


void ThreadPool::workerThread()
{
	while (true)
	{
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			condition.wait(lock, [this] { return stop || !tasks.empty(); });
			if (stop && tasks.empty())
			{
				return;
			}
			task = std::move(tasks.front());
			tasks.pop();
		}
		task();
	}
}

using Matrix = std::vector<std::vector<int>>;


int computeOneElement(const Matrix& firstMatrix, const Matrix& secondMatrix, int rowIndex, int columnIndex)
{
	int result = 0;
	for (size_t k = 0; k < firstMatrix[0].size(); ++k)
	{
		result += firstMatrix[rowIndex][k] * secondMatrix[k][columnIndex];
	}
	return result;
}


std::pair<int, int> getTaskRange(int taskNumber, int totalTasks, int totalElements)
{
	const int elementsPerTask = totalElements / totalTasks;
	const int rest = totalElements % totalTasks;
	const int start = taskNumber * elementsPerTask + std::min(taskNumber, rest);
	const int end = start + elementsPerTask + (taskNumber < rest ? 1 : 0);
	return { start, end };
}


void computeMatrixRow(const Matrix& firstMatrix, const Matrix& secondMatrix, Matrix& resultMatrix, int taskNumber, int totalTasks)
{
	int totalElements = firstMatrix.size() * secondMatrix[0].size();
	std::pair<int, int> range = getTaskRange(taskNumber, totalTasks, totalElements);
	int start = range.first;
	int end = range.second;
	int columns = secondMatrix[0].size();
	for (int i = start; i < end; ++i)
	{
		int row = i / columns;
		int col = i % columns;
		resultMatrix[row][col] = computeOneElement(firstMatrix, secondMatrix, row, col);
	}
}


void printMatrix(const Matrix& matrix)
{
	for (const auto& row : matrix)
	{
		for (const auto& element : row)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	const int SIZE = 1000;
    Matrix firstMatrix(SIZE, std::vector<int>(SIZE)); 
    Matrix secondMatrix(SIZE, std::vector<int>(SIZE)); 
    Matrix resultMatrix(SIZE, std::vector<int>(SIZE, 0));

	std::srand(std::time(0));

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            firstMatrix[i][j] = 1;
            secondMatrix[i][j] = 1;
        }
    }


	int numberOfThreads = 2;
	ThreadPool threadPool(numberOfThreads);

	auto startTime = std::chrono::high_resolution_clock::now();

	int rowsPerThread = firstMatrix.size() / numberOfThreads;
	for (int i = 0; i < numberOfThreads; ++i)
	{
		int startRow = i * rowsPerThread;
		int endRow = (i == numberOfThreads - 1) ? SIZE : startRow + rowsPerThread;

		threadPool.enqueue([&, i, numberOfThreads]()
		{
			computeMatrixRow(firstMatrix, secondMatrix, resultMatrix, i, numberOfThreads);
		});
	}


	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = endTime - startTime;

	// std::cout << "Resulted matrix:" << std::endl;
	// printMatrix(resultMatrix);

    std::cout << "Matrices sizes: " << SIZE << std::endl;
	std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;

	return 0;
}
