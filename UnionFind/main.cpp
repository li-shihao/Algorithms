#include <cstdio>
#include <vector>
#include <valarray>
using namespace std;

vector<int> pset(1000);
void initSet(int _size) {
    pset.resize(_size);
    for (int i = 0; i < _size; i++) {
        pset[i] = i;
    }
}
int findSet(int i) {
    return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}
void unionSet(int i, int j) {
    pset[findSet(i)] = findSet(j);
}
bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}
int numberOfSets() {
    std::valarray<int> sets(pset.size());
    for (int i = 0; i < pset.size(); i++) {
        sets[findSet(i)] = 1;
    }
    return sets.sum();
}
int sizeOfSet(int j) {
    int sum = 0;
    for (int i = 0; i < pset.size(); i++) {
        if(findSet(i) == j) {
            sum += 1;
       }
    }
    return sum;
}
int main() {
    initSet(5);
    unionSet(1,4);
    if (isSameSet(1,4)) puts("true"); 
    else puts("false");
    printf("%d\n", numberOfSets());
    printf("%d\n", sizeOfSet(4));
    return 0;
}
