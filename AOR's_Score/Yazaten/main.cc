#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define all(a)  (a).begin(),(a).end()
#define pb emplace_back
#define INF (1e9+1)
//#define INF (1LL<<59)

//verified POJ3680
#define MAX_V 204
struct edge { int to, cap, cost,rev; };

vector<edge> G[MAX_V];
vector<int> h(MAX_V);	//ポテンシャル
vector<int> dist(MAX_V);// 最短距離
int prevv[MAX_V], preve[MAX_V];// 直前の頂点と辺

// fromからtoへ向かう容量cap、コストcostの辺をグラフに追加する
void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
    G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
}

//コストが負の辺が含まれない場合は不要
void shortest_path(int s,vector<int> &d){
    int v = d.size();
    rep(i,d.size())d[i]=INF;
    d[s]=0;
    rep(loop,v){
        rep(i,v){
            for(auto e:G[i]){
                if(e.cap && d[i]!=INF && d[e.to] > d[i]+e.cost)
                    d[e.to] = d[i]+e.cost;
            }
        }
    }
}


// sからtへの流量fの最小費用流を求める
// 流せない場合は-1を返す
int min_cost_flow(int s, int t, int f) {
    int res = 0;
    shortest_path(s, h);
    
    while (f > 0) {
        // ダイクストラ法を用いてhを更新する
        priority_queue<pii, vector<pii>, greater<pii> > que;
        rep(i,dist.size())dist[i]=INF;
        dist[s] = 0;
        que.push(pii(0, s));
        while (!que.empty()) {
            pii p = que.top(); que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to]; prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(pii(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == INF) return -INF;	//これ以上流せない
        
        for (int v = 0; v < h.size(); v++) h[v] += dist[v];
        
        
        // s-t間最短路に沿って目一杯流す
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]]; e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}


int main(){
    int N,M,K;
    cin>>N>>M>>K;
    vector<vector<int>> score(M+1,vector<int>(N));
    
    rep(i,N)cin>>score[M][i];
    rep(i,M) rep(j,N)cin>>score[i][j];
    
    vector<int> lim(M);
    rep(i,M)cin>>lim[i];
    
    int V = N + M+1 + 1 + 2;
    
    const int X = V-3;
    const int s = V-2;
    const int t = V-1;
    
    //始点Sから各問題を表す頂点に、容量 1 /コスト 0 の有向辺を貼る
    rep(i,N){
        add_edge(s, i, 1, 0);
    }
    
    //各問題を表す頂点から各生徒を表す頂点に、容量 1 /コスト 「(-1)*(その問題をその生徒が解いたときの点数) 」 の有向辺を貼る
    rep(i,N){
        for(int j=N;j<N+M+1;j++){
            add_edge(i, j, 1, -1*score[j-N][i]);
        }
    }

    //自分を除く各生徒を表すM個の頂点から写す回数を制限するための頂点に、 容量 「(その生徒が写させてくれる回数の上限)」 /コスト 0 の有向辺を貼る
    for(int j=N;j<N+M;j++){
        add_edge(j, X, lim[j-N], 0);
    }
    
    //自分を表す頂点から終点Tに、容量 ∞ /コスト 0 の有向辺を貼る
    add_edge(N+M, t, INF, 0);
    
    //写す回数を制限するための頂点からTに、容量 N-K /コスト0 の辺を貼る
    add_edge(X, t, N-K, 0);
    
    
    // const auto f = [&](int n){
    //     if(n>=90*N)return 'A';
    //     if(n>=70*N)return 'B';
    //     if(n>=50*N)return 'C';
    //     return 'F';
    // };
    
    int res = -1*min_cost_flow(s, t, N);
    // cout<<res<<" "<<f(res)<<endl;
    cout << res << endl;
}
