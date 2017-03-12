#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <queue>
using namespace std;

vector<int> g[MAX_N];

bool isMultipleEdges(int a, int b){ //多重辺及び逆辺検知
    for(int i = 0; i < g[a].size(); i++){
        if(g[a][i] == b) return true;
    }
    return false;
}

bool isSelfLoop(int a, int b){
    return a == b;
}

bool isLinking(int n){
    bool isVisited[MAX_N] = {0};
    queue<int> q;

    isVisited[0] = 1;
    q.push(0);

    int u;
    while(not q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < g[u].size(); i++){
            int next = g[u][i];
            if(isVisited[next] == 0){
                q.push(next);
                isVisited[next] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(isVisited[i] == 0) return false;
    }
    return true;
}

int min(int a, int b){
    if(a >= b) return b;
    else return a;
}

int main(){
	registerValidation();

    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int M = inf.readInt(N - 1, min(MAX_M, N * (N - 1) / 2));
    inf.readSpace();
    int T = inf.readInt(MIN_T, MAX_T);
    inf.readEoln();

    for(int i = 0; i < M; i++){
        int a = inf.readInt(1,N);
        inf.readSpace();
        int b = inf.readInt(1,N);
        inf.readSpace();
        inf.readInt(1,T);
        inf.readEoln();

        a--; b--;
        assert(not isMultipleEdges(a, b));
        assert(not isSelfLoop(a, b));
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    assert(isLinking(N));

	inf.readEof();
}
