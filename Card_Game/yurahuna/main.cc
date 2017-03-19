#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
using ll = long long;
const ll inf = 1ll << 60;

struct edge {
    int to;
	ll cost;
    edge(){}
    edge(int _to, ll _cost) : to(_to), cost(_cost) {}
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

	vector<vector<ll>> d(R, vector<ll>(N + 1, inf));
	using State = pair<ll, int>;
	rep(r, R) {
		priority_queue<State, vector<State>, greater<State>> pq;   // cost, vertex
		for (int i = r; i <= N; i += R) {
			if (i == 0) continue;
			d[r][i] = 0ll;
			pq.push(State(0ll, i));
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

	ll sm = 0ll;
	rep(i, Q) {
		int x, y;
		ll z;
		cin >> x >> y >> z;
		ll ma = 0ll;
		rep(r, R) {
			ma = max(ma, z - d[r][x] - d[r][y]);
		}
		sm += ma;
	}
	cout << sm << endl;
}
