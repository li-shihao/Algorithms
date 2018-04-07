#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2
using namespace std;

typedef vector<int> vi;

vi segment_tree;

void init_segment_tree(int N) {
  int length = (int)(2 * pow(2.0, floor((log((double)N) / log(2.0)) + 1)));
  segment_tree.resize(length, 0);
}

void build_segment_tree(int code, int A[], int node, int b, int e) {
  if (b == e) {
    if (code == RANGE_SUM)
      segment_tree[node] = A[b];
    else
      segment_tree[node] = b;
  } else {
    int leftIdx = 2 * node, rightIdx = 2 * node + 1;
    build_segment_tree(code, A, leftIdx, b, (b + e) / 2);
    build_segment_tree(code, A, rightIdx, (b + e) / 2 + 1, e);
    int lContent = segment_tree[leftIdx], rContent = segment_tree[rightIdx];

    if (code == RANGE_SUM)
      segment_tree[node] = lContent + rContent;
    else {
      int lValue = A[lContent], rValue = A[rContent];
      if (code == RANGE_MIN)
        segment_tree[node] = (lValue <= rValue) ? lContent : rContent;
      else
        segment_tree[node] = (lValue >= rValue) ? lContent : rContent;
    }
  }
}

int query(int code, int A[], int node, int b, int e, int i, int j) {
  if (i > e || j < b) return -1;
  if (b >= i && e <= j) return segment_tree[node];

  int p1 = query(code, A, 2 * node, b, (b + e) / 2, i, j);
  int p2 = query(code, A, 2 + node + 1, (b + e) / 2 + 1, e, i, j);

  if (p1 == -1) return p2;
  if (p2 == -1) return p1;

  if (code == RANGE_SUM)
    return p1 + p2;
  else if (code == RANGE_MIN)
    return (A[p1] <= A[p2]) ? p1 : p2;
  else
    return (A[p1] >= A[p2]) ? p1 : p2;
}

void update(int code, int A[], int idx, int val, int from, int to, int node) {
  if (from == to && code == RANGE_SUM)
    segment_tree[node] = val;
  else if (from == to)
    return;
  else {
    int left = 2 * node, right = left + 1, mid = (from + to) / 2;
    if (idx > mid)
      update(code, A, idx, val, mid + 1, to, right);
    else
      update(code, A, idx, val, from, mid, left);

    int lContent = segment_tree[left], rContent = segment_tree[right];
    if (code == RANGE_SUM)
      segment_tree[node] = lContent + rContent;
    else {
      int lValue = A[lContent], rValue = A[rContent];
      if (code == RANGE_MIN)
        segment_tree[node] = (lValue <= rValue) ? lContent : rContent;
      else
        segment_tree[node] = (lValue >= rValue) ? lContent : rContent;
    }
  }
}

int main() {
  int A[] = {8, 7, 3, 9, 5, 1, 10};
  init_segment_tree(7);
  build_segment_tree(RANGE_MIN, A, 1, 0, 6);
  printf("%d\n", query(RANGE_MIN, A, 1, 0, 6, 0, 6));
  A[5] = 100;
  update(RANGE_MIN, A, 5, 100, 0, 6, 1);
  printf("%d\n", query(RANGE_MIN, A, 1, 0, 6, 0, 6));
  return 0;
}
