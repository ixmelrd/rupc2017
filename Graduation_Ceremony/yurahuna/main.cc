#include <iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
#define chmax(a,b) (a)=max((a),(b));
const int inf = 1e9;

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
        
        rep(k, 2) { // 正 or 負
            rep(i, (int)t.size() + 1) rep(j, K + 1) dp[l][k][i][j] = -inf;
            dp[l][k][0][0] = 0;
            rep(i, (int)t.size()) {
                rep(j, K + 1) {
                    if (dp[l][k][i][j] == -inf) continue;
                    int diff = !k ? +1 : -1;
                    if ( (!l && t[i] == 'L') || (l && t[i] == 'D') ) diff *= -1;
                    if (j % 2) diff *= -1;
                    chmax(dp[l][k][i + 1][j], dp[l][k][i][j] + diff);
                    if (j < K) chmax(dp[l][k][i + 1][j + 1], dp[l][k][i][j] + (-1) * diff);
                }
            }
        }

        rep(j, K + 1) {
            dp_abs[l][j] = max(dp[l][0][(int)t.size()][j], dp[l][1][(int)t.size()][j]);
        }
    }

    int ans = 0;
    rep(j0, K + 1) {
        rep(j1, K + 1 - j0) {
            chmax(ans, dp_abs[0][j0] + dp_abs[1][j1]);
        }
    }
    cout << ans << endl;
}
