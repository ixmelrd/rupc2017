#include "./testlib.h"
#include "./constraints.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

bool isMultipleEdges(int a, int b, vector<int> v[MAX_N]){
    for(int i = 0; i < v[a].size(); i++){
        if(v[a][i] == b) return true;
    }
    return false;
}

bool isSelfLoop(int a, int b){
    return a == b;
}

int main(){
    registerValidation();

    int n = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int m = inf.readInt(MIN_M, (int)min<long long int>(MAX_M,(long long int)(n)*(n-1)));
    inf.readSpace();
    inf.readInt(MIN_R, MAX_R);
    inf.readSpace();
    int q = inf.readInt(MIN_Q, MAX_Q);
    inf.readEoln();

    vector<int> v[MAX_N];
    for(int i = 0; i < m; i++){
        int a = inf.readInt(MIN_a_b, n);
        inf.readSpace();
        int b = inf.readInt(MIN_a_b, n);
        inf.readSpace();
        inf.readInt(MIN_c, MAX_c);
        inf.readEoln();

        a--; b--;
        assert(not isMultipleEdges(a,b,v));
        assert(not isSelfLoop(a,b));
        v[a].emplace_back(b);
    }

    for(int i = 0; i < q; i++){
        inf.readInt(MIN_x_y, n);
        inf.readSpace();
        inf.readInt(MIN_x_y, n);
        inf.readSpace();
        inf.readInt(MIN_z, MAX_z);
        inf.readEoln();
    }

    inf.readEof();
}
