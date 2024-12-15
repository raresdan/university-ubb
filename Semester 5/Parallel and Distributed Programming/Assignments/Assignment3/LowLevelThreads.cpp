#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>
#include <cstdlib>


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


void computeMatrixColumn(const Matrix& firstMatrix, const Matrix& secondMatrix, Matrix& resultMatrix, int taskNumber, int totalTasks)
{
	int totalElements = firstMatrix.size() * secondMatrix[0].size();
	std::pair<int, int> range = getTaskRange(taskNumber, totalTasks, totalElements);
	int start = range.first;
	int end = range.second;
	int rows = firstMatrix.size();
	for (int i = start; i < end; ++i)
	{
		int row = i / rows;
		int col = i % rows;
		resultMatrix[row][col] = computeOneElement(firstMatrix, secondMatrix, row, col);
	}
}


void computeMatrixElementsByStride(const Matrix& firstMatrix, const Matrix& secondMatrix, Matrix& resultMatrix, int taskNumber, int totalTasks)
{
	int rows = firstMatrix.size();
	int columns = secondMatrix[0].size();
	for (int i = taskNumber; i < rows * columns; i += totalTasks)
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
	std::vector<std::thread> threads;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numberOfThreads; ++i)
	{
		threads.emplace_back(computeMatrixRow, std::ref(firstMatrix), std::ref(secondMatrix), std::ref(resultMatrix), i, numberOfThreads);
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = endTime - startTime;

	// std::cout << "Resulted matrix:" << std::endl;
	// printMatrix(resultMatrix);

	std::cout << "Matrices sizes: " << SIZE << std::endl;
	std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;

	return 0;
}
