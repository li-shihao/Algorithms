#include <algorithm>
#include <cstdio>
#include <vector>
#define N 4

using namespace std;
typedef std::vector<pair<int, int> > vii;

bool isSafe(int maze[N][N], int x, int y) {
  return (x < N && x >= 0 && y < N && y >= 0 && maze[x][y] == 1);
}

void printMaze(int maze[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (maze[i][j] == 2)
        printf("1   ");
      else
        printf("0   ");
    }
    printf("\n");
  }
  printf("\n");
}

int getValidMoves(int maze[N][N], int x, int y, pair<int, int> moves[4]) {
  int ValidMoves = 0;
  for (int i = 0; i < 4; i++) {
    int nextX = x + moves[i].first;
    int nextY = y + moves[i].second;
    if (isSafe(maze, nextX, nextY)) {
      ValidMoves++;
    }
  }
  return ValidMoves;
}

vii rankMoves(int maze[N][N], int x, int y, pair<int, int> moves[4]) {
  vii ranks;
  for (int i = 0; i < 4; i++) {
    int nextX = x + moves[i].first;
    int nextY = y + moves[i].second;
    if (isSafe(maze, nextX, nextY)) {
      ranks.push_back(make_pair(getValidMoves(maze, x, y, moves), i));
    }
  }
  sort(ranks.begin(), ranks.end());
  return ranks;
}

bool solve(int maze[N][N], int x, int y, pair<int, int> moves[4]) {
  if (maze[3][3] == 2) return true;
  vii ranks(rankMoves(maze, x, y, moves));
  for (int i = 0; i < ranks.size(); i++) {
    int j = ranks[i].second;
    int nextX = x + moves[j].first;
    int nextY = y + moves[j].second;

    maze[nextX][nextY] = 2;
    if (solve(maze, nextX, nextY, moves))
      return true;
    else
      maze[nextX][nextY] = 1;
  }
  return false;
}

void init() {
  pair<int, int> moves[4] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1),
                             make_pair(0, -1)};
  int maze[N][N] = {{2, 0, 0, 0}, {1, 1, 0, 1}, {0, 1, 0, 0}, {1, 1, 1, 1}};
  if (solve(maze, 0, 0, moves) == false) {
    printf("Solution not found");
  } else
    printMaze(maze);
}

int main() {
  init();
  return 0;
}
