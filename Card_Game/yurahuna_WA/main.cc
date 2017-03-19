#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)
#define chmin(a,b) (a)=min((a),(b));
#define chmax(a,b) (a)=max((a),(b));
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define printV(v) cerr<<(#v)<<":";for(auto(x):(v)){cerr<<" "<<(x);}cerr<<endl;
#define printVS(vs) cerr<<(#vs)<<":"<<endl;for(auto(s):(vs)){cerr<<(s)<< endl;}
#define printVV(vv) cerr<<(#vv)<<":"<<endl;for(auto(v):(vv)){for(auto(x):(v)){cerr<<" "<<(x);}cerr<<endl;}
#define printP(p) cerr<<(#p)<<(p).first<<" "<<(p).second<<endl;
#define printVP(vp) cerr<<(#vp)<<":"<<endl;for(auto(p):(vp)){cerr<<(p).first<<" "<<(p).second<<endl;}

inline void output(){ cerr << endl; }
template<typename First, typename... Rest>
inline void output(const First& first, const Rest&... rest) {
    cerr << first << " "; output(rest...);
}

using ll = long long;
using Pii = pair<int, int>;
using TUPLE = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int inf = 1e9;

// 誤解法
// オーバーフロー
// (Q=10^5 回のゲームで毎回 10^5 の利益が得られるとすると答えは 10^10)

struct edge {
    int to, cost;
    edge(){}
    edge(int _to, int _cost) : to(_to), cost(_cost) {}
};
using Graph = vector<vector<edge>>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int N, M, R, Q;
	cin >> N >> M >> R >> Q;
	Graph G(N + 1);
	rep(i, M) {
		int a, b, c;
		cin >> a >> b >> c;
		G[b].emplace_back(a, c); // !!逆向きに辺を張る!!
	}

	vvi d(R, vi(N + 1, inf));
	using State = pair<int, int>;
	rep(r, R) {
		priority_queue<State, vector<State>, greater<State>> pq;   // cost, vertex
		for (int i = r; i <= N; i += R) {
			if (i == 0) continue;
			d[r][i] = 0;
			pq.push(State(0, i));
		}
		while (!pq.empty()) {
			auto p = pq.top(); pq.pop();
			int v = p.second;
			if (d[r][v] < p.first) continue;
			for (const auto& e : G[v]) {
				if (d[r][e.to] > d[r][v] + e.cost) {
					d[r][e.to] = d[r][v] + e.cost;
					pq.push(State(d[r][e.to], e.to));
				}
			}
		}
	}

	// printVV(d);

	int sm = 0;
	rep(i, Q) {
		int x, y, z;
		cin >> x >> y >> z;
		int ma = 0;
		rep(r, R) {
			ma = max(ma, z - d[r][x] - d[r][y]);
		}
		sm += ma;
	}
	cout << sm << endl;
}
