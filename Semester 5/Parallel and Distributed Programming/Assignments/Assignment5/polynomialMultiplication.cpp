#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>

const int NAIVE_SEQ = 1;
const int NAIVE_PAR = 2;
const int KARATSUBA_SEQ = 3;
const int KARATSUBA_PAR = 4;

int n, numThreads, algorithm;

std::mutex mtx;

std::vector<int> firstPolynomial, secondPolynomial, resultPolynomial;
std::vector<std::thread> threads;

std::vector<int> polynomialMultiplication(const std::vector<int> &firstPolynomial,const std::vector<int> &secondPolynomial)
{
    std::vector<int> resultPoly(firstPolynomial.size() + secondPolynomial.size() - 1, 0);
    for (int i = 0; i < firstPolynomial.size(); i++)
    {
        for (int j = 0; j < secondPolynomial.size(); j++)
        {
            resultPoly[i+j] += firstPolynomial[i] * secondPolynomial[j];
		}
    }
    return resultPoly;
}

void parallelPolynomialMultiplication(int startIndex)
{
    int currentDegree = startIndex;
    for (; currentDegree < n; currentDegree += numThreads)
    {
        // solve for position currDegree
        for (int x = 0; x <= currentDegree; x++)
        {
            int y = currentDegree - x;
            resultPolynomial[currentDegree] += firstPolynomial[x] * secondPolynomial[y];
        }
    }
    for (; currentDegree < 2 * n - 1; currentDegree += numThreads)
    {
        // solve for position currDegree
        for (int x = currentDegree - n + 1; x < n; x++)
        {
            int y = currentDegree - x;
            resultPolynomial[currentDegree] += firstPolynomial[x] * secondPolynomial[y];
        }
    }
}

// Function to addPolynomials two polynomials
std::vector<int> addPolynomials(const std::vector<int>& firstPolynomial, const std::vector<int>& secondPolynomial)
{
    int maxSize = std::max(firstPolynomial.size(), secondPolynomial.size());
    std::vector<int> resultPoly(maxSize, 0);
    for (int i = 0; i < maxSize; ++i)
    {
        if (i < firstPolynomial.size())
        {
            resultPoly[i] += firstPolynomial[i];
        }
        if (i < secondPolynomial.size())
        {
            resultPoly[i] += secondPolynomial[i];
        }
    }
    return resultPoly;
}

// Function to subtractPolynomials two polynomials
std::vector<int> subtractPolynomials(const std::vector<int>& firstPolynomial, const std::vector<int>& secondPolynomial)
{
    int maxSize = std::max(firstPolynomial.size(), secondPolynomial.size());
    std::vector<int> resultPoly(maxSize, 0);
    for (int i = 0; i < maxSize; ++i)
    {
        if (i < firstPolynomial.size())
        {
            resultPoly[i] += firstPolynomial[i];
        }
        if (i < secondPolynomial.size())
        {
            resultPoly[i] -= secondPolynomial[i];
        }
    }
    return resultPoly;
}

// Karatsuba algorithm for polynomial multiplication
std::vector<int> karatsubaSequential(const std::vector<int>& firstPolynomial, const std::vector<int>& secondPolynomial)
{
    size_t size = std::max(firstPolynomial.size(), secondPolynomial.size());

    // Base case for recursion
    if (size <= 100)
    {
        return polynomialMultiplication(firstPolynomial, secondPolynomial);
    }

    // Making the degree of polynomials even
    size_t halfSize = (size + 1) / 2;

    std::vector<int> firstLow(firstPolynomial.begin(), firstPolynomial.begin() + std::min(halfSize, firstPolynomial.size()));
    std::vector<int> firstHigh(firstPolynomial.begin() + std::min(halfSize, firstPolynomial.size()), firstPolynomial.end());
    std::vector<int> secondLow(secondPolynomial.begin(), secondPolynomial.begin() + std::min(halfSize, secondPolynomial.size()));
    std::vector<int> secondHigh(secondPolynomial.begin() + std::min(halfSize, secondPolynomial.size()), secondPolynomial.end());

    std::vector<int> firstLowHigh = addPolynomials(firstHigh, firstLow);
    std::vector<int> secondLowHigh = addPolynomials(secondHigh, secondLow);

    // Recursive calls
    std::vector<int> z0 = karatsubaSequential(firstLow, secondLow);
    std::vector<int> z1 = karatsubaSequential(firstLowHigh, secondLowHigh);
    std::vector<int> z2 = karatsubaSequential(firstHigh, secondHigh);

    // Combining the results
    std::vector<int> temp = subtractPolynomials(z1, z0);
    temp = subtractPolynomials(temp, z2);

    std::vector<int> resultPoly(firstPolynomial.size() + secondPolynomial.size() - 1, 0);
    for (int i = 0; i < z0.size(); i++)
    {
        resultPoly[i] += z0[i];
    }
    for (int i = 0; i < temp.size(); i++)
    {
        resultPoly[i + halfSize] += temp[i];
    }
    for (int i = 0; i < z2.size(); i++)
    {
        resultPoly[i + 2 * halfSize] += z2[i];
    }
    return resultPoly;
}

std::vector<int> karatsubaParallel(const std::vector<int>& firstPolynomial, const std::vector<int>& secondPolynomial)
{
    size_t size = std::max(firstPolynomial.size(), secondPolynomial.size());

    // Base case for recursion
    if (size <= 100)
    {
        return polynomialMultiplication(firstPolynomial, secondPolynomial);
    }

    // Making the degree of polynomials even
    size_t halfSize = (size + 1) / 2;

    std::vector<int> firstLow(firstPolynomial.begin(), firstPolynomial.begin() + std::min(halfSize, firstPolynomial.size()));
    std::vector<int> firstHigh(firstPolynomial.begin() + std::min(halfSize, firstPolynomial.size()), firstPolynomial.end());
    std::vector<int> secondLow(secondPolynomial.begin(), secondPolynomial.begin() + std::min(halfSize, secondPolynomial.size()));
    std::vector<int> secondHigh(secondPolynomial.begin() + std::min(halfSize, secondPolynomial.size()), secondPolynomial.end());

    std::vector<int> z0, z1, z2, resultPoly(firstPolynomial.size() + secondPolynomial.size() - 1, 0);
    
    std::vector<int> firstLowHigh = addPolynomials(firstHigh, firstLow);
    std::vector<int> secondLowHigh = addPolynomials(secondHigh, secondLow);

    std::thread t0([&]
        {
            z0 = karatsubaParallel(firstLow, secondLow);
            mtx.lock();
            for (int i = 0; i < z0.size(); i++)
            {
                resultPoly[i] += z0[i];
            }
            mtx.unlock();
        });
    std::thread t2([&]
        {
			z2 = karatsubaParallel(firstHigh, secondHigh);
            mtx.lock();
            for (int i = 0; i < z2.size(); i++)
            {
                resultPoly[i + 2 * halfSize] += z2[i];
            }
            mtx.unlock();
		});
    std::thread t1([&]
        {
            z1 = karatsubaParallel(firstLowHigh, secondLowHigh);
		});
    
    t0.join();
	t1.join();
	t2.join();

	std::vector<int> temp = subtractPolynomials(z1, z0);
	temp = subtractPolynomials(temp, z2);
    
    for (int i = 0; i < temp.size(); i++)
    {
		resultPoly[i + halfSize] += temp[i];
	}
    
	return resultPoly;
}

void printVector(std::vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

void initialiseData()
{
    std::cout << "Enter size: ";
    std::cin >> n;
    if (algorithm == NAIVE_PAR)
    {
        std::cout << "Enter number of threads: ";
        std::cin >> numThreads;
    }
    for (int i = 0; i < n; ++i)
    {
       firstPolynomial.push_back(1);
       secondPolynomial.push_back(1);
    }

    resultPolynomial.resize(2 * n - 1, 0);
}

void solve()
{
    clock_t time = clock();

    initialiseData();

    if (algorithm == NAIVE_SEQ)
    {
       	polynomialMultiplication(firstPolynomial, secondPolynomial);
    }
    else if (algorithm == NAIVE_PAR)
    {
        for (int i = 0; i < std::min(n, numThreads); i++)
        {
            threads.push_back(std::thread(parallelPolynomialMultiplication, i));
        }
        // join threads
        for (int i = 0; i < threads.size(); i++)
        {
            threads[i].join();
        }
    }
    else if (algorithm == KARATSUBA_SEQ)
    {
		resultPolynomial = karatsubaSequential(firstPolynomial, secondPolynomial);
	}
    else if (algorithm == KARATSUBA_PAR)
    {
		resultPolynomial = karatsubaParallel(firstPolynomial, secondPolynomial);
	}

    time = clock() - time;
    std::cout << "Total time: " << static_cast<float>(time) / CLOCKS_PER_SEC << " seconds\n";
}

void printMenu()
{
    std::cout << "Choose algorithm:\n";
    std::cout << "1. Naive\n";
    std::cout << "2. Naive with threads\n";
    std::cout << "3. Karatsuba\n";
    std::cout << "4. Karatsuba with threads\n";
}

void getAlgorithm()
{
	std::cout << "Enter algorithm: ";
	std::cin >> algorithm;
    if (algorithm < 1 || algorithm > 5)
    {
		std::cout << "Invalid algorithm\n";
		getAlgorithm();
	}
}

bool getPrintVector()
{
	std::cout << "Do you want to print the result vector? 1 - Yes, 0 - No\n";
    bool print;
    std::cin >> print;
    return print;
}

void mainApp()
{
    printMenu();
    getAlgorithm();
    solve();
    if (getPrintVector())
    {
        printVector(resultPolynomial);
    }
}

int main()
{
    mainApp();
}