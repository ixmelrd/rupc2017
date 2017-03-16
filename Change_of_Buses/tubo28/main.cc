#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

const int INF = 1e9;

using Weight = int;
using Flow = int;
struct Edge {
    int src, dst;
    Weight weight;
    Flow cap;
    Edge() : src(0), dst(0), weight(0) {}
    Edge(int s, int d, Weight w) : src(s), dst(d), weight(w) {}
};
using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
using Array = std::vector<Weight>;
using Matrix = std::vector<Array>;

void add_arc(Graph &g, int a, int b, Weight w = 1) { g[a].emplace_back(a, b, w); }

std::vector<Weight> dijkstra(const Graph &g, int s) {
    const Weight INF = std::numeric_limits<Weight>::max() / 8;
    using state = std::tuple<Weight, int>;
    std::priority_queue<state> q;
    std::vector<Weight> dist(g.size(), INF);
    dist[s] = 0;
    q.emplace(0, s);
    while (q.size()) {
        Weight d;
        int v;
        std::tie(d, v) = q.top();
        q.pop();
        d *= -1;
        /* if(v == t) return d; */
        if (dist[v] < d) continue;
        for (auto &e : g[v]) {
            if (dist[e.dst] > dist[v] + e.weight) {
                dist[e.dst] = dist[v] + e.weight;
                q.emplace(-dist[e.dst], e.dst);
            }
        }
    }
    return dist;
}

ll enc(int v, int t) {
    return (ll)v*1000000000 + t;
}
pair<int,int> dec(ll x) {
    return make_pair(x/1000000000, x%1000000000);
}

int main(){
    int n, m, s, t;
    while (cin >> n >> m >> s >> t) {
        --s; --t;
        vector<vector<int>> ts(n);
        vector<tuple<int, int, int, int, int>> es; // (バス停,つく時間), (バス停,つく時間), 濡れる時間
        ts[s].emplace_back(0);
        rep (i, m) {
            int u, v, t, c;
            cin >> u >> v >> t >> c;
            --u; --v;
            es.emplace_back(u, t, v, t + c, 0);
            ts[u].emplace_back(t);
            ts[v].emplace_back(t + c);
        }
        rep (i, n) {
            sort(all(ts[i]));
            rep (j, ts[i].size() - 1) {
                int t1 = ts[i][j], t2 = ts[i][j+1];
                es.emplace_back(i, t1, i, t2, t2 - t1);
            }
        }

        map<ll, int> mp;
        for (auto &e : es) {
            int a, b, c, d;
            tie(a, b, c, d, ignore) = e;
            mp[enc(a, b)];
            mp[enc(c, d)];
        }
        int id = 0;
        for (auto &e : mp) {
            e.second = id++;
        }

        Graph g(id);
        for (auto &e : es){
            int a, b, c, d, w;
            tie(a, b, c, d, w) = e;
            int u = mp[enc(a, b)];
            int v = mp[enc(c, d)];
            add_arc(g, u, v, w);
        }

        vector<Weight> dist = dijkstra(g, mp[enc(s, 0)]);

        int ans = INF;
        for (auto &e : mp) {
            int v;
            tie(v, ignore) = dec(e.first);
            if (v == t) ans = min(ans, dist[e.second]);
        }
        cout << ans << endl;
    }
}
