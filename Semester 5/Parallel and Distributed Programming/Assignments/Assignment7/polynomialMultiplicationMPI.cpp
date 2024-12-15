#include <iostream>
#include <vector>
#include <mpi.h>
#include <cmath>

// Function to multiply two polynomials (O(n^2))
std::vector<int> polynomialMultiplication(const std::vector<int> &A, const std::vector<int> &B) {
    int n = A.size(), m = B.size();
    std::vector<int> result(n + m - 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i + j] += A[i] * B[j];
        }
    }
    return result;
}

// Function to add two polynomials
std::vector<int> addPolynomials(const std::vector<int> &A, const std::vector<int> &B) {
    int n = std::max(A.size(), B.size());
    std::vector<int> result(n, 0);

    for (int i = 0; i < n; ++i) {
        if (i < A.size()) result[i] += A[i];
        if (i < B.size()) result[i] += B[i];
    }
    return result;
}

// Function to subtract two polynomials
std::vector<int> subtractPolynomials(const std::vector<int> &A, const std::vector<int> &B) {
    int n = std::max(A.size(), B.size());
    std::vector<int> result(n, 0);

    for (int i = 0; i < n; ++i) {
        if (i < A.size()) result[i] += A[i];
        if (i < B.size()) result[i] -= B[i];
    }
    return result;
}

// Karatsuba algorithm for polynomial multiplication
std::vector<int> karatsuba(const std::vector<int> &A, const std::vector<int> &B) {
    int n = std::max(A.size(), B.size());

    // Base case: use the naive method
    if (n <= 100) {
        return polynomialMultiplication(A, B);
    }

    int half = n / 2;

    // Split polynomials into low and high parts
    std::vector<int> A_low(A.begin(), A.begin() + std::min(half, (int)A.size()));
    std::vector<int> A_high(A.begin() + std::min(half, (int)A.size()), A.end());
    std::vector<int> B_low(B.begin(), B.begin() + std::min(half, (int)B.size()));
    std::vector<int> B_high(B.begin() + std::min(half, (int)B.size()), B.end());

    // Recursive calls
    std::vector<int> z0 = karatsuba(A_low, B_low);
    std::vector<int> z1 = karatsuba(addPolynomials(A_low, A_high), addPolynomials(B_low, B_high));
    std::vector<int> z2 = karatsuba(A_high, B_high);

    // Combine results
    std::vector<int> result(A.size() + B.size() - 1, 0);
    for (int i = 0; i < z0.size(); ++i) result[i] += z0[i];
    for (int i = 0; i < z1.size(); ++i) result[i + half] += z1[i] - z0[i] - z2[i];
    for (int i = 0; i < z2.size(); ++i) result[i + 2 * half] += z2[i];

    return result;
}

// Distributed polynomial multiplication using MPI
void mpiPolynomialMultiplication(const std::vector<int> &A, const std::vector<int> &B, std::vector<int> &result, int rank, int size) {
    int n;

    // Broadcast polynomial size to all processes
    if (rank == 0) {
        n = A.size();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Adjust input vectors for non-root processes
    std::vector<int> local_A(n, 0), local_B(n, 0);
    if (rank == 0) {
        local_A = A;
        local_B = B;
    }
    MPI_Bcast(local_B.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter segments of the first polynomial
    int segmentSize = (n + size - 1) / size;  // Ceiling division
    std::vector<int> A_segment(segmentSize, 0);
    MPI_Scatter(local_A.data(), segmentSize, MPI_INT, A_segment.data(), segmentSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute partial product
    std::vector<int> partialResult(A_segment.size() + local_B.size() - 1, 0);
    for (int i = 0; i < A_segment.size(); ++i) {
        for (int j = 0; j < local_B.size(); ++j) {
            if (i + j < partialResult.size()) {
                partialResult[i + j] += A_segment[i] * local_B[j];
            }
        }
    }

    // Gather all partial results at the root process
    int resultSize = n * 2 - 1;
    std::vector<int> allPartialResults(rank == 0 ? resultSize * size : 0, 0);
    MPI_Gather(partialResult.data(), partialResult.size(), MPI_INT, allPartialResults.data(), partialResult.size(), MPI_INT, 0, MPI_COMM_WORLD);

    // Combine results at the root process
    if (rank == 0) {
        result.assign(resultSize, 0);
        for (int i = 0; i < size; ++i) {
            int offset = i * segmentSize;
            for (int j = 0; j < partialResult.size(); ++j) {
                if (offset + j < result.size()) {
                    result[offset + j] += allPartialResults[i * partialResult.size() + j];
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> A, B, result;
    int n;

    if (rank == 0) {
        // Input polynomials at the root process
        std::cout << "Enter the degree of the polynomials: ";
        std::cin >> n;
        A.resize(n, 1);  // Example: initialize A with ones
        B.resize(n, 1);  // Example: initialize B with ones
    }

    double start = MPI_Wtime();

    // Perform distributed polynomial multiplication
    mpiPolynomialMultiplication(A, B, result, rank, size);

    double end = MPI_Wtime();

    if (rank == 0) {
        // Print the result at the root process
        std::cout << "Result: ";
        for (int i : result) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << "Time: " << end - start << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}


// Run with:
// mpic++ polynomialMultiplicationMPI.cpp -o polynomialMultiplicationMPI
// mpirun -np <num_processes> ./polynomialMultiplicationMPI