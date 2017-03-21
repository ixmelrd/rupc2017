#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)

// 誤解法
// 入力において x が y の親であると仮定して書いた

const int MAX = 100010;
double prob_pow[MAX];   // prob_pow[i]  = p^i
int depth[MAX];         // depth[v]     = 頂点 v の深さ
int depth_cnt[MAX];     // depth_cnt[i] = "depth[v] = i" なる v の個数

struct edge {
    int to;
    double cost;
    edge(){}
    edge(int _to, double _cost) : to(_to), cost(_cost) {}
};
using Graph = vector<vector<edge>>;

void setDepth(int v, int pre, int dep, const Graph& G) {
    depth[v] = dep;
    depth_cnt[dep]++;
    for (auto e : G[v]) {
        if (e.to == pre) continue;
        setDepth(e.to, v, dep + 1, G);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	prob_pow[0] = 1.;
	cin >> prob_pow[1];
	rep2(i, 1, MAX - 1) prob_pow[i + 1] = prob_pow[i] * prob_pow[1];

    int n;
	cin >> n;

    Graph G(n);
    rep(i, n - 1) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        a--; b--;
        G[a].emplace_back(b, c);
        G[b].emplace_back(a, c);
    }

    setDepth(0, -1, 0, G);

    double A = prob_pow[1];
    rep(i, MAX - 1) {
        A += depth_cnt[i] * prob_pow[i + 1];
    }

    double ans = 0.;
    rep(v, n) {
        for (auto e : G[v]) {
            if (depth[v] >= depth[e.to]) continue;
            ans += A * prob_pow[depth[v]] * e.cost;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
