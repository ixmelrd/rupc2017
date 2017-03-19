#include <iostream>
#include <iomanip>
#include <vector>
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

void setDepth(int v, int dep, const Graph& G) {
    depth[v] = dep;
    depth_cnt[dep]++;
    for (auto e : G[v]) {
        setDepth(e.to, dep + 1, G);
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

    // rep(i, n) {
    //     cerr << (i ? " " : "") << prob_pow[i];
    // }
    // cerr << endl;

    Graph G(n);
    rep(i, n - 1) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        a--; b--;
        G[a].emplace_back(b, c);
    }

    setDepth(0, 0, G);

    rep(v, n) {
        cerr << (v ? " " : "") << depth[v];
    }
    cerr << endl;

    rep(i, n) {
        cerr << (i ? " " : "") << depth_cnt[i];
    }
    cerr << endl;

    double A = 0.;
    rep(i, MAX - 1) {
        A += depth_cnt[i] * prob_pow[i + 1];
        cerr << depth_cnt[i] << " " << prob_pow[i + 1] << endl;
    }
    A += prob_pow[1];
    cerr << A << endl;

    double ans = 0.;
    rep(v, n) {
        for (auto e : G[v]) {
            cerr << v << " " << prob_pow[depth[v]] << " " << e.to << " " << e.cost << endl;
            ans += A * prob_pow[depth[v]] * e.cost;
            // ans += prob_pow[depth[v] + 1] * e.cost;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
