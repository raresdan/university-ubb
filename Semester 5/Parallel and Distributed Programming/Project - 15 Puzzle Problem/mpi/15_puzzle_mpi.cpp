#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <mpi.h>

using namespace std;

template <typename T1, typename T2>
struct Pair {
  T1 first;
  T2 second;

  Pair(T1 f, T2 s) : first(f), second(s) {}
};

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

    if (emptyRow > 0) { // Up
      Matrix newMatrix = *this;
      swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow - 1][emptyCol]);
      newMatrix.calculateManhattan();
      newMatrix.numberOfSteps = numberOfSteps + 1;
      moves.push_back(newMatrix);
    }
    if (emptyRow < 3) { // Down
      Matrix newMatrix = *this;
      swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow + 1][emptyCol]);
      newMatrix.calculateManhattan();
      newMatrix.numberOfSteps = numberOfSteps + 1;
      moves.push_back(newMatrix);
    }
    if (emptyCol > 0) { // Left
      Matrix newMatrix = *this;
      swap(newMatrix.grid[emptyRow][emptyCol], newMatrix.grid[emptyRow][emptyCol - 1]);
      newMatrix.calculateManhattan();
      newMatrix.numberOfSteps = numberOfSteps + 1;
      moves.push_back(newMatrix);
    }
    if (emptyCol < 3) { // Right
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

  friend ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        os << matrix.grid[i][j] << " ";
      }
      os << endl;
    }
    return os;
  }
};

Pair<int, Matrix> search(const Matrix& current, int numSteps, int bound) {
  if (numSteps + current.manhattan > bound) {
    return {numSteps + current.manhattan, current};
  }
  if (numSteps + current.manhattan > 100) { 
    return {numSteps + current.manhattan, current};
  }
  if (current.manhattan == 0) {
    return {-1, current};
  }

  int minimum = numeric_limits<int>::max();
  Matrix bestSolution;

  for (const Matrix& next : current.generateMoves()) {
    Pair<int, Matrix> result = search(next, numSteps + 1, bound);
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

Pair<int, Matrix> searchMPI(const Matrix& current, int numSteps, int bound, int rank, int numProcesses) {
  if (numSteps + current.manhattan > bound) {
    return {numSteps + current.manhattan, current};
  }
  if (numSteps + current.manhattan > 100) { 
    return {numSteps + current.manhattan, current};
  }
  if (current.manhattan == 0) {
    return {-1, current};
  }

  vector<Matrix> moves = current.generateMoves();
  int movesPerProcess = (moves.size() + numProcesses - 1) / numProcesses; // Distribute moves across processes
  int start = rank * movesPerProcess;
  int end = min((rank + 1) * movesPerProcess, static_cast<int>(moves.size()));

  int minimum = numeric_limits<int>::max();
  Matrix bestSolution;

  for (int i = start; i < end; ++i) {
    Pair<int, Matrix> result = search(moves[i], numSteps + 1, bound);
    if (result.first == -1) {
      return {-1, result.second};
    }
    if (result.first < minimum) {
      minimum = result.first;
      bestSolution = result.second;
    }
  }

  Pair<int, Matrix> result = {minimum, bestSolution};
  return result;
}

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank, numProcesses;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

  Matrix initialState;
  if (rank == 0) {
    initialState = Matrix::readFromFile("input.in");
  }

  MPI_Bcast(&initialState, sizeof(Matrix), MPI_BYTE, 0, MPI_COMM_WORLD);

  int minimumBound = initialState.manhattan;
  int distance;

  while (true) {
    double startTime = MPI_Wtime();

    Pair<int, Matrix> solution = searchMPI(initialState, 0, minimumBound, rank, numProcesses);

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
  }

  MPI_Finalize();
  return 0;
}
