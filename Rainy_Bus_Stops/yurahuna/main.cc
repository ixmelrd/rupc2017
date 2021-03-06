#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()

// (バス停, 時刻)のペアを頂点としてダイクストラ
// 辺は「バスでの移動」または「同じバス停で次の時刻まで待つ」をあらわす
// このグラフの頂点数，辺数はともに O(M)
// map を使っているので O(M * (logM)^2)

using Vertex = pair<int, int>; // バス停，時刻
struct edge {
    Vertex to;
	int cost; // 濡れる時間
    edge(){}
    edge(Vertex _to, int _cost) : to(_to), cost(_cost) {}
};
using Graph = map<Vertex, vector<edge>>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n, m, s, g;
	cin >> n >> m >> s >> g;
	s--; g--;

	Graph G;
	vector<Vertex> vertices;
	const Vertex start_vertex(s, 0);
	vertices.emplace_back(start_vertex);
	rep(i, m) {
		int u, v, t, c;
		cin >> u >> v >> t >> c;
		u--; v--;
		G[Vertex(u, t)].emplace_back(Vertex(v, t + c), 0);
		G[Vertex(v, t + c)];
		vertices.emplace_back(u, t);
		vertices.emplace_back(v, t + c);
	}

	sort(all(vertices));
	vertices.erase(unique(all(vertices)), vertices.end());

	rep(i, (int)vertices.size() - 1) {
		if (vertices[i].first == vertices[i + 1].first) {
			G[vertices[i]].emplace_back(vertices[i + 1], vertices[i + 1].second - vertices[i].second);
		}
	}

    using State = pair<int, Vertex>;
    priority_queue<State, vector<State>, greater<State>> pq; // cost, vertex
	map<Vertex, int> d;
    d[start_vertex] = 0;
    pq.push(State(0, start_vertex));
    while (!pq.empty()) {
		int cost;
		Vertex vertex;
        tie(cost, vertex) = pq.top(); pq.pop();
        if (vertex.first == g) {
			cout << cost << endl;
			return 0;
		}
        if (d.count(vertex) && d[vertex] < cost) continue;
        for (const auto& e : G[vertex]) {
            if (!d.count(e.to) || d[e.to] > cost + e.cost) {
                d[e.to] = cost + e.cost;
                pq.push(State(d[e.to], e.to));
            }
        }
    }
}
