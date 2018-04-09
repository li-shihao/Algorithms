#include <algorithm>
#include <cstdio>
#include <vector>
#define N 5
typedef std::vector<int> vi;
vi sub;

void printSet() {
  for (int i = 0; i < sub.size(); i++) {
    printf("%i ", sub[i]);
  }
  printf("\n");
}

bool solve(int arr[N], int ans, int current, int pos) {
  if (current == ans) {
    return true;
  }
  for (int i = pos; i < N; i++) {
    if (current + arr[i] <= ans) {
      current += arr[i];
      sub.push_back(arr[i]);
      if (solve(arr, ans, current, pos + 1))
        return true;
      else {
        sub.pop_back();
        current -= arr[i];
        pos--;
      }
    }
  }
  return false;
}

void init() {
  vi sub;
  int arr[N] = {1, 2, 3, 4, 5};
  int ans = 8;
  if (solve(arr, ans, 0, 0))
    printSet();
  else
    printf("Solution not found");
}

int main() {
  init();
  return 0;
}
