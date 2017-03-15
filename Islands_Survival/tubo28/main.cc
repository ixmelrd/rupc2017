#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

struct uf_tree {
    vector<int> parent;
    int __size;
    uf_tree(int size_) : parent(size_, -1), __size(size_) { }
    void unite(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (parent[y] < parent[x]) swap(x, y);
            parent[x] += parent[y];
            parent[y] = x;
            __size--;
        }
    }
    bool is_same(int x, int y) { return find(x) == find(y); }
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    int size(int x) { return -parent[find(x)]; }
    int size() { return __size; }
};

struct node {
    int find, size, time;
    vector<node*> ch;
    node(int f, int s, int t, vector<node*> c)
        : find(f), size(s), time(t), ch(c) {}
    node() {}
    void *operator new(size_t) {
        static node pool[200010];
        static node *p = pool;
        return p++;
    }
};

using np = node*;

const int INF = 1e18;

using edge = tuple<int,int,int>;
int N, M, K, T;
edge edges[100010];
np uf_state[100010];
map<int,vector<edge>> events;
vector<edge> g[100010];

int dist[100010];

int dfs(np n, int cur){
    int ans;
    if(n->ch.size()){
        ans = -INF;
        for(auto &c : n->ch){
            int cand = (n->time - cur) * n->size + dfs(c, n->time);
            ans = max(ans, cand);
        }
    } else {
        ans = dist[n->find] != INF ? (n->time - cur) * n->size : -INF;
    }
    return ans;
}

void show(np n, int d = 0){
    cout << string(d, ' ') << "root:" << n->find << " size:" << n->size << " time:" << n->time << endl;
    for(auto &c : n->ch){
        cout << string(d, ' ') << "(\n";
        show(c, d+2);
        cout << string(d, ' ') << ")\n";
    }
}

signed main(){
    cin >> N >> M >> T;
    rep(i, M){
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        g[a].emplace_back(a, b, t);
        g[b].emplace_back(b, a, t);
        events[-t].emplace_back(t, a, b);
    }

    uf_tree uf(N);
    rep(i, N) uf_state[i] = new node(i, 1, T, {}); // 時間Tですべての辺が消えると考える

    // もっときれいな実装方法があると思う
    vector<np> org(N);
    for(auto &ev : events){
        static map<int, set<np>> collect;
        collect.clear();

        int cur = -ev.first;
        auto &es = ev.second;
        for(auto &e : es){
            int t, a, b;
            tie(t, a, b) = e;
            org[a] = uf_state[uf.find(a)];
            org[b] = uf_state[uf.find(b)];
        }
        for(auto &e : es){
            int t, a, b;
            tie(t, a, b) = e;
            uf.unite(a, b);
        }
        for(auto &e : es){
            int t, a, b;
            tie(t, a, b) = e;
            collect[uf.find(a)].insert(org[a]);
            collect[uf.find(b)].insert(org[b]);
        }
        for(auto &e : collect){
            int v = e.first;
            uf_state[v] = new node(v, uf.size(v), cur, vector<np>(all(e.second)));
            // show(uf_state[v]);
        }
    }

    fill(dist, dist + N, INF);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while(q.size()){
        int v = q.front();
        q.pop();
        for(auto &e : g[v]){
            int d, t;
            tie(ignore, d, t) = e;
            if(dist[d] == INF && dist[v] < t){
                dist[d] = dist[v] + 1;
                q.push(d);
            }
        }
    }

    // show(uf_state[uf.find(0)]);
    cout << dfs(uf_state[uf.find(0)], 0) << endl;
}
