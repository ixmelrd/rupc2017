#include <iostream>
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

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int inf = 1e9;
const int mod = 1e9 + 7;
using Graph = vector<vector<int>>;

// dp[i][j] = s[0, i) を処理するまでに魔法を j 回かけたときの，座標の最大値
// dp_abs[j] = 文字を全て処理するまでに魔法を j 回かけたときの，座標の絶対値の最大値

const int MAX = 2010;
int dp[2][2][MAX][MAX];
int dp_abs[2][MAX];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    string s;
    cin >> s;
    int K;
    cin >> K;

    rep(l, 2) { // 左右 or 上下
        string t;
        for (auto c : s) {
            if ( (!l && (c == 'L' || c == 'R')) || (l && (c == 'D' || c == 'U')) ) {
                t += c;
            }
        }
        // cerr << t << endl;

        rep(k, 2) { // 正 or 負
            rep(i, (int)t.size() + 1) rep(j, K + 1) dp[l][k][i][j] = -inf;
            dp[l][k][0][0] = 0;
            rep(i, (int)t.size()) {
                rep(j, K + 1) {
                    if (dp[l][k][i][j] == -inf) continue;
                    int diff = !k ? +1 : -1;
                    if ( (!l && t[i] == 'L') || (l==1 && t[i] == 'D') ) diff *= -1;
                    if (j % 2) diff *= -1;
                    chmax(dp[l][k][i + 1][j], dp[l][k][i][j] + diff);
                    if (j < K) chmax(dp[l][k][i + 1][j + 1], dp[l][k][i][j] + (-1) * diff);

                    // output("i =", i, ", j =", j);
                    // rep(_i, (int)t.size() + 1) {
                    //     rep(_j, K + 1) {
                    //         cerr << (_j ? " " : "") << dp[l][k][_i][_j];
                    //     }
                    //     cerr << endl;
                    // }
                    // cerr << endl;
                }
            }

            // rep(i, (int)t.size() + 1) {
            //     rep(j, K + 1) {
            //         cerr << (j ? " " : "") << dp[l][k][i][j];
            //     }
            //     cerr << endl;
            // }
            // cerr << endl;
        }

        rep(j, K + 1) {
            dp_abs[l][j] = max(dp[l][0][(int)t.size()][j], dp[l][1][(int)t.size()][j]);
        }

        // rep(j, K + 1) {
        //     cerr << (j ? " " : "") << dp_abs[l][j];
        // }
        // cerr << endl;

        output("dp_abs[l][0] =", dp_abs[l][0]);

    }


    // rep(i, (int)t.size() + 1) {
    //     rep(j, K + 1) {
    //         cerr << (j ? " " : "") << dp[i][j];
    //     }
    //     cerr << endl;
    // }

    int ans = 0;
    rep(j0, K + 1) {
        rep2(j1, K - j0, K + 1) { // j0 + j1 == K の場合しか調べていない (本当は j0 + j1 <= K)
        // rep(j1, K + 1 - j0) {
            chmax(ans, dp_abs[0][j0] + dp_abs[1][j1]);
        }
    }
    cout << ans << endl;

}
