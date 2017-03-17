#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 114514;
#define REP(i,n) for(int i=0;i<(int)n;++i)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()
#define RESIDUE(u,v) (capacity[u][v] - flow[u][v])
#define RCOST(u,v) (cost[u][v] + h[u] - h[v])

typedef int Weight;
struct Edge {
  int src, dst;
  int capacity;
  Weight cost;
 
  Edge(int src, int dst) :
	src(src), dst(dst) { }
  Edge(int src, int dst, int capacity,Weight cost) :
	src(src), dst(dst), cost(cost),capacity(capacity) { }
};
bool operator < (const Edge &e, const Edge &f) {
  return e.cost != f.cost ? e.cost > f.cost : // !!INVERSE!!
	e.src != f.src ? e.src < f.src : e.dst < f.dst;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

typedef vector<Weight> Array;
typedef vector<Array> Matrix;

	
int minimumCostFlow(const Graph &g, int s, int t,int S,int T) {
  const int n = g.size();
  Matrix capacity(n, Array(n)), cost(n, Array(n)), flow(n, Array(n));
  REP(u,n) FOR(e,g[u]) {
	capacity[e->src][e->dst] += e->capacity;
	cost[e->src][e->dst] += e->cost;
  }
	auto f = [&](int s,int t){
	  pair<Weight, Weight> total; // (cost, flow)
	  vector<Weight> h(n);
	  for (Weight F = INF; F > 0; ) { // residual flow
		vector<Weight> d(n, INF); d[s] = 0;
		vector<int> p(n, -1);
		priority_queue<Edge> Q; // "e < f" <=> "e.cost > f.cost"
		for (Q.push(Edge(-2, s)); !Q.empty(); ) {
		  Edge e = Q.top(); Q.pop();
		  if (p[e.dst] != -1) continue;
		  p[e.dst] = e.src;
		  FOR(f, g[e.dst]) if (RESIDUE(f->src, f->dst) > 0) {
			if (d[f->dst] > d[f->src] + RCOST(f->src, f->dst)) {
			  d[f->dst] = d[f->src] + RCOST(f->src, f->dst);
			  Q.push( Edge(f->src, f->dst, 0, d[f->dst]) );
			}
		  }
		}
		if (p[t] == -1) break;

		Weight f = F;
		for (int u = t; u != s; u = p[u])
		  f = min(f, RESIDUE(p[u], u));
		for (int u = t; u != s; u = p[u]) {
		  total.first += f * cost[p[u]][u];
		  flow[p[u]][u] += f; flow[u][p[u]] -= f;
		}
		F -= f;
		total.second += f;
		REP(u, n) h[u] += d[u];
	  }
	  return total;
  };
  int tot = 0;
  f(S,T);
  f(S,t);
  f(s,T);
  f(s,t);
  int ans = 0;
  for(int i = 0 ; i < n ; i++){
  	for(int j = 0 ; j < n ; j++){
  		if( flow[i][j] > 0 ){
  			ans += flow[i][j] * cost[i][j];
  		}
	}
  }
  return ans;
  
}


// 最小流量つき最小費用流(のつもり)

int main(){
	int b[110][110], lim[110];
	int N,M,K;
	cin >> N >> M >> K;
	
	for(int i = 0 ; i < N ; i++){
		cin >> b[M][i];	
	}
	for(int i = 0 ; i < M ; i++){
		for(int j = 0 ; j < N ; j++){
			cin >> b[i][j];
		}
	}
	for(int i = 0 ; i < M ; i++) cin >> lim[i];
	
	Graph g( N + (M+1) + 2 + 2 ); // N + M + (me) + (superVs) + (superVs for lowerbound)
	
	const int s = g.size() -1;
	const int t = g.size() - 2;
	const int S = g.size() -3;
	const int T = g.size() - 4;
	const auto task = [&](int x){ return x; };
	const auto person = [&](int x){ return x + N; };
	const int me = N + M;
	
	const auto add_edge = [&](const Edge &e){
		g[e.src].push_back(e);
		g[e.dst].push_back(Edge(e.dst,e.src,0,-e.cost));
	};
	
	for(int i = 0 ; i < N ; i++){
		add_edge(Edge(s,task(i),1,0));		
	}
	for(int i = 0 ; i < M ; i++){
		add_edge(Edge(person(i),t,lim[i],0));
	}	
	// [K,N]: range of amount of flow for (me)
	// http://snuke.hatenablog.com/entry/2016/07/10/043918
	
	add_edge(Edge(me,t,N-K,0));
	add_edge(Edge(me,T,K,0));
	add_edge(Edge(S,t,K,0));
	
	for(int i = 0 ; i < N ; i++){
		for(int j = 0 ; j <= M ; j++){
			add_edge(Edge(task(i),person(j),1,100 - b[j][i]));
		}
	}
	
	int pts = N * 100 - minimumCostFlow(g,s,t,S,T);
	cout << pts << endl;
}