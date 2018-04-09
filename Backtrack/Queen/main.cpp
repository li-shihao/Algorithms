#include <algorithm>
#include <cstdio>
#include <vector>
#define N 10

using namespace std;

void printBoard(int[N][N]);
bool isSafe(int board[N][N], int x, int y) {
  return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == 0);
}

bool checkAdjacent(int board[N][N], int x, int y) {
  for (int i = 0; i < N; i++) {
    if (!isSafe(board, i, y)) return false;
  }
  for (int j = 0; j < N; j++) {
    if (!isSafe(board, x, j)) return false;
  }

  int h = x, v = y;
  while (h > 0 && v > 0) {
    h--;
    v--;
  }
  while (h < N && v < N) {
    if (!isSafe(board, h, v)) return false;
    h++;
    v++;
  }

  int a = x, b = y;
  while (a < (N - 1) && b < (N - 1)) {
    a++;
    b++;
  }

  while (a >= 0 && b >= 0) {
    if (!isSafe(board, a, b)) return false;
    a--;
    b--;
  }

  return true;
}

bool solve(int board[N][N], int x) {
  if (x == N) return true;
  for (int j = 0; j < N; j++) {
    if (checkAdjacent(board, x, j)) {
      board[x][j] = 1;
      if (solve(board, x + 1))
        return true;
      else
        board[x][j] = 0;
    }
  }
  return false;
}

void init() {
  int board[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = 0;
    }
  }
  if (solve(board, 0))
    printBoard(board);
  else
    printf("Solution does not exist\n");
}

void printBoard(int board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%i    ", board[i][j]);
    }
    printf("\n");
  }
}

int main() {
  init();
  return 0;
}
