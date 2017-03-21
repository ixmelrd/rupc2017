#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

class Edge{
    public:
        int to, cost;
        Edge(int to, int cost) : to(to) ,cost(cost) {}
};

typedef vector<vector<Edge>> AdjList;

bool isTree(AdjList g, int n){
    vector<bool> isUsed(n,0);
    queue<int> q;

    q.push(0);

    int u;
    while(not q.empty()){
        u = q.front(); q.pop();
        isUsed[u] = 1;

        for(int i = 0; i < g[u].size(); i++){
            int next = g[u][i].to;
            if(isUsed[next] == 0){
                q.push(next);
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(isUsed[i] == 0) return false;
    }
    return true;
}


int main(){
    registerValidation();

    inf.readDouble(MIN_p, MAX_p);
    inf.readEoln();

    int A = inf.readInt(MIN_A, MAX_A);
    AdjList treeA(A);
    inf.readEoln();
    for(int i = 0; i < A - 1; i++){
        int a = inf.readInt(MIN_v, A);
        inf.readSpace();
        int b = inf.readInt(MIN_v, A);
        inf.readSpace();
        int c = inf.readInt(MIN_c, MAX_c);
        inf.readEoln();

        a--; b--;
        treeA[a].emplace_back(b,c);
        treeA[b].emplace_back(a,c);
    }
    assert(isTree(treeA, A));

    /*
    int B = inf.readInt(MIN_B, MAX_B);
    AdjList treeB(B);
    inf.readEoln();
    for(int i = 0; i < B - 1; i++){
        int a = inf.readInt(MIN_v, B);
        inf.readSpace();
        int b = inf.readInt(MIN_v, B);
        inf.readSpace();
        int c = inf.readInt(MIN_c, MAX_c);
        inf.readEoln();

        a--; b--;
        treeB[a].emplace_back(b,c);
        treeB[b].emplace_back(a,c);
    }
    assert(isTree(treeB, B));
    */
    
    inf.readEof();
}
