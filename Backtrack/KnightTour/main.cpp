#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define N 50
bool backtrack(int, int, int, int[N][N], int[8], int[8]);

bool isSafe(int x, int y, int board[N][N]) {
  return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

void printSolution(int board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%2d   ", board[i][j]);
    }
    printf("\n");
  }
}

void init() {
  int board[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = -1;
    }
  }
  int xMoves[] = {1, 2, -1, -2, 1, 2, -1, -2};
  int yMoves[] = {2, 1, 2, 1, -2, -1, -2, -1};
  board[0][0] = 0;
  if (backtrack(0, 0, 1, board, xMoves, yMoves) == false) {
    printf("solution does not exist");
  } else
    printSolution(board);
}

int getValidMoves(int board[N][N], int x, int y, int xMoves[8], int yMoves[8]) {
  int sum;
  for (int i = 0; i < 8; i++) {
    if (isSafe(x + xMoves[i], y + yMoves[i], board)) {
      sum++;
    }
  }
  return sum;
}

vector<pair<int, int> > rankMoves(int board[N][N], int x, int y, int xMoves[8],
                                  int yMoves[8]) {
  vector<pair<int, int> > moves;
  for (int i = 0; i < 8; i++) {
    int nextX = x + xMoves[i], nextY = y + yMoves[i];
    if (isSafe(nextX, nextY, board)) {
      int temp = getValidMoves(board, nextX, nextY, xMoves, yMoves);
      if (temp >= 1)
        moves.push_back(
            make_pair(getValidMoves(board, nextX, nextY, xMoves, yMoves), i));
    }
  }
  sort(moves.begin(), moves.end());
  return moves;
}

bool backtrack(int x, int y, int step, int board[N][N], int xMoves[8],
               int yMoves[8]) {
  if (step == N * N) return true;
  vector<pair<int, int> > Moves(rankMoves(board, x, y, xMoves, yMoves));
  for (int i = 0; i < Moves.size(); i++) {
    int j = Moves[i].second;
    int nextX = x + xMoves[j], nextY = y + yMoves[j];
    board[nextX][nextY] = step;
    if (backtrack(nextX, nextY, step + 1, board, xMoves, yMoves) == true) {
      return true;
    } else
      board[nextX][nextY] = -1;
  }
  return false;
}

int main() {
  init();
  return 0;
}
