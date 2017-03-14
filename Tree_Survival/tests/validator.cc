#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <queue>
using namespace std;

vector<int> g[MAX_N];
vector<pair<int, int>> edges;

bool isSimple() {
    sort(edges.begin(), edges.end());
    for (auto &e : edges) {
        if (e.first > e.second) swap(e.first, e.second);
    }
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto &e = edges[i];
        if (e.first == e.second) return false;
        if (i + 1 != (int)edges.size()) {
            auto &f = edges[i + 1];
            if (e == f) return false;
        }
    }
    return true;
}

bool isConnected(int n){
    bool isVisited[MAX_N] = {0};
    queue<int> q;

    isVisited[0] = 1;
    q.push(0);

    int u;
    while(not q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < (int)g[u].size(); i++){
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
    int M = inf.readInt(N - 1, (int)min((long long)MAX_M, (long long)N * (N - 1) / 2));
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
        g[a].emplace_back(b);
        g[b].emplace_back(a);
        edges.emplace_back(a, b);
    }

    assert(isConnected(N));
    assert(isSimple());

	inf.readEof();
}
