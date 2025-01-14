#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <mpi.h>

using namespace std;

class Matrix {
public:
    int grid[4][4];
    int manhattan;
    int numberOfSteps;

    Matrix() {
        manhattan = 0;
        numberOfSteps = 0;
    }

    void calculateManhattan() {
        manhattan = 0;
        int goal[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (grid[i][j] != 0) {
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            if (grid[i][j] == goal[k][l]) {
                                manhattan += abs(i - k) + abs(j - l);
                            }
                        }
                    }
                }
            }
        }
    }

    vector<Matrix> generateMoves() const {
        vector<Matrix> moves;
        int emptyRow, emptyCol;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (grid[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                    break;
                }
            }
        }

        if (emptyRow > 0) {
            Matrix newMatrix = *this;
            swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow - 1][emptyCol]);
            newMatrix.calculateManhattan();
            newMatrix.numberOfSteps = numberOfSteps + 1;
            moves.push_back(newMatrix);
        }
        if (emptyRow < 3) {
            Matrix newMatrix = *this;
            swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow + 1][emptyCol]);
            newMatrix.calculateManhattan();
            newMatrix.numberOfSteps = numberOfSteps + 1;
            moves.push_back(newMatrix);
        }
        if (emptyCol > 0) {
            Matrix newMatrix = *this;
            swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow][emptyCol - 1]);
            newMatrix.calculateManhattan();
            newMatrix.numberOfSteps = numberOfSteps + 1;
            moves.push_back(newMatrix);
        }
        if (emptyCol < 3) {
            Matrix newMatrix = *this;
            swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow][emptyCol + 1]);
            newMatrix.calculateManhattan();
            newMatrix.numberOfSteps = numberOfSteps + 1;
            moves.push_back(newMatrix);
        }

        return moves;
    }

    static Matrix readFromFile(string filename) {
        Matrix initialMatrix;
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening input file." << endl;
            exit(1);
        }

        string line;
        int row = 0;
        while (getline(infile, line)) {
            istringstream iss(line);
            int col = 0;
            while (iss >> initialMatrix.grid[row][col]) {
                col++;
            }
            row++;
        }

        infile.close();
        initialMatrix.calculateManhattan();
        return initialMatrix;
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                os << matrix.grid[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
};

pair<int, Matrix> search(const Matrix &current, int numSteps, int bound) {
    if (numSteps + current.manhattan > bound) {
        return {numSteps + current.manhattan, current};
    }
    if (current.manhattan == 0) {
        return {-1, current};
    }

    int minimum = numeric_limits<int>::max();
    Matrix bestSolution;

    for (const Matrix &next : current.generateMoves()) {
        pair<int, Matrix> result = search(next, numSteps + 1, bound);
        if (result.first == -1) {
            return {-1, result.second};
        }
        if (result.first < minimum) {
            minimum = result.first;
            bestSolution = result.second;
        }
    }

    return {minimum, bestSolution};
}

pair<int, Matrix> searchMPI(const Matrix &current, int numSteps, int bound, int rank, int numProcesses) {
    vector<Matrix> moves = current.generateMoves();
    int movesPerProcess = (moves.size() + numProcesses - 1) / numProcesses;
    int start = rank * movesPerProcess;
    int end = min((rank + 1) * movesPerProcess, static_cast<int>(moves.size()));

    int localMin = numeric_limits<int>::max();
    Matrix localBestSolution;

    for (int i = start; i < end; ++i) {
        pair<int, Matrix> result = search(moves[i], numSteps + 1, bound);
        if (result.first == -1) {
            return {-1, result.second};
        }
        if (result.first < localMin) {
            localMin = result.first;
            localBestSolution = result.second;
        }
    }

    int globalMin;
    MPI_Reduce(&localMin, &globalMin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0 && globalMin == -1) {
        return {-1, localBestSolution};
    }

    return {globalMin, localBestSolution};
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    Matrix initialState;
    int grid[16];

    if (rank == 0) {
        initialState = Matrix::readFromFile("input.in");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                grid[i * 4 + j] = initialState.grid[i][j];
            }
        }
    }

    MPI_Bcast(grid, 16, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                initialState.grid[i][j] = grid[i * 4 + j];
            }
        }
        initialState.calculateManhattan();
    }

    int minimumBound = initialState.manhattan;
    int distance;

    while (true) {
        double startTime = MPI_Wtime();

        pair<int, Matrix> solution = searchMPI(initialState, 0, minimumBound, rank, numProcesses);

        double endTime = MPI_Wtime();

        if (rank == 0) {
            distance = solution.first;

            if (distance == -1) {
                cout << solution.second.numberOfSteps << " steps - "
                     << (endTime - startTime) * 1000 << " ms" << endl;
                cout << solution.second << endl;
                break;
            } else {
                cout << distance << " steps - "
                     << (endTime - startTime) * 1000 << " ms" << endl;
            }

            minimumBound = distance;
        }

        MPI_Bcast(&minimumBound, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
