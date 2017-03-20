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
    node *ch[2];
    node(int f, int s, int t, node *left, node *right)
        : find(f), size(s), time(t) {
        ch[0] = left;
        ch[1] = right;
    }
    node() {}
    void *operator new(size_t) {
        static node pool[300010];
        static node *p = pool;
        return p++;
    }
};

using np = node*;
const int INF = 1e18;
using edge = tuple<int,int,int>;

int N, M, K, T;
vector<edge> g[100010];

int dist[100010];

int dfs(np n, int cur){
    int ans;
    if(n->ch[0]){
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

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> N >> M >> T;
    vector<tuple<int,int,int>> edges;
    rep(i, M){
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        g[a].emplace_back(a, b, t);
        g[b].emplace_back(b, a, t);
        edges.emplace_back(t, a, b);
    }

    vector<np> uf_state(N);
    uf_tree uf(N);
    rep(i, N) uf_state[i] = new node(i, 1, T, nullptr, nullptr); // 時間Tですべての辺が消えると考える

    sort(all(edges));
    reverse(all(edges));
    for(auto &e : edges){
        int t, a, b;
        tie(t, a, b) = e;
        if (uf.is_same(a, b)) continue;
        np org_a = uf_state[uf.find(a)];
        np org_b = uf_state[uf.find(b)];
        uf.unite(a, b);
        uf_state[uf.find(a)] = new node(uf.find(a), uf.size(a), t, org_a, org_b);
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

    cout << dfs(uf_state[uf.find(0)], 0) << endl;
}
