#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

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

const int NR_THREADS = 8;


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

Pair<int, Matrix> searchParallel(const Matrix& current, int numSteps, int bound, int nrThreads) {
  if (nrThreads <= 1) {
    return search(current, numSteps, bound);
  }

  if (numSteps + current.manhattan > bound) {
    return {numSteps + current.manhattan, current};
  }
  if (numSteps + current.manhattan > 100) { 
    return {numSteps + current.manhattan, current};
  }
  if (current.manhattan == 0) {
    return {-1, current};
  }

  vector<future<Pair<int, Matrix>>> futures;
  vector<Matrix> moves = current.generateMoves();

  int threadsPerMove = max(1, static_cast<int>(nrThreads / moves.size()));
  for (const Matrix& next : moves) {
    futures.push_back(async(launch::async, searchParallel, ref(next), numSteps + 1, bound, threadsPerMove));
  }

  int minimum = numeric_limits<int>::max();
  Matrix bestSolution;

  for (auto& future : futures) {
    Pair<int, Matrix> result = future.get();
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

// Main function
int main() {
  Matrix initialState = Matrix::readFromFile("input.in");

  int minimumBound = initialState.manhattan;
  int distance;

  while (true) {
    auto start = chrono::high_resolution_clock::now();
    Pair<int, Matrix> solution = searchParallel(initialState, 0, minimumBound, NR_THREADS);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    distance = solution.first;

    if (distance == -1) {
      cout << solution.second.numberOfSteps << " steps - " << duration.count() << "ms" << endl;
      cout << solution.second << endl;
      break;
    } else {
      cout << distance << " steps - " << duration.count() << "ms" << endl;
    }

    minimumBound = distance;
  }

  return 0;
}