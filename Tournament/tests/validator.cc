#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <algorithm>
using namespace std;

int popcount(int n) {
    return n ? popcount(n/2) + n%2 : 0;
}

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N, MAX_N);
    assert(popcount(N) == 1);
    inf.readSpace();
    int M = inf.readInt(MIN_M, N);
    inf.readEoln();
    vector<int> a(M);
    for (int i = 0; i < M; ++i) {
        a[i] = inf.readInt(0, N - 1);
        inf.readEoln();
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < M; ++i) {
        assert(a[i] != a[i-1]);
    }
    inf.readEof();
}
