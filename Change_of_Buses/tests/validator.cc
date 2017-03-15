#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int,int> pii;
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)
#define INF 999999999

struct edge{int to,cost;};

void dijkstra(int s, vector<int> &d, vector<edge> G[MAX_N]){
    priority_queue< pii,vector<pii>,greater<pii> > que;
    rep( i,d.size() )d[i]=INF;
    d[s] = 0;
    que.push( pii(0,s) );
    
    while( que.size() ){
        pii p=que.top();
        que.pop();
        
        int v=p.second;
        if(d[v]<p.first)continue;
        
        rep(i,G[v].size()){
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost){
                d[e.to]=d[v]+e.cost;
                que.push(pii(d[e.to],e.to));
            }
        }
    }
}


bool isReachable(int v, int s, int g, vector<edge> graph[MAX_M]){
	vector<int> d(v);
	dijkstra(s,d,graph);

	if(d[g]<INF)return true;
	else return false;
}

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N,MAX_N);
    inf.readSpace();
    int M = inf.readInt(MIN_M,MAX_M);
    inf.readSpace();
    int S = inf.readInt(MIN_S,N);
    inf.readSpace();
    int G = inf.readInt(MIN_G,N);
    inf.readEoln();

    assert(S!=G);
    S--,G--;

    vector<edge> graph[MAX_N];
    rep(i,M){
    	int u = inf.readInt(MIN_u,N);
    	inf.readSpace();
    	int v = inf.readInt(MIN_v,N);
    	inf.readSpace();
    	inf.readInt(MIN_t,MAX_t);
    	inf.readSpace();
    	inf.readInt(MIN_c,MAX_c);
		inf.readEoln();
    	u--,v--;
    	graph[u].pb(edge{v,0});
    }

    assert( isReachable(N, S, G, graph) );

    inf.readEof();
}
