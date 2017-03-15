#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

const int INF = 1e9;

string s;
int k;

int dp[2010][2010];

void solve(const string &a, char add, int res[2010]) {
    int n = a.size();
    rep(i, n+1) rep(j, k+1) dp[i][j] = -INF;
    dp[0][0] = 0;
    rep (i, n) {
        rep (j, k+1) {
            int d = a[i] == add ? +1 : -1;
            if (j % 2 == 1) d *= -1;
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + d);
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] - d);
        }
    }
    res[0] = dp[n][0];
    rep (i, k + 1) if (i) res[i] = max(res[i-1], dp[n][i]);
}

int main() {
    cin >> s >> k;
    string a, b;
    for (char c : s) {
        if (c == 'U' || c == 'D') {
            a += c;
        } else {
            b += c;
        }
    }
    int dp[4][2010];
    solve(a, 'U', dp[0]);
    solve(a, 'D', dp[1]);
    solve(b, 'L', dp[2]);
    solve(b, 'R', dp[3]);
    int ans = -INF;
    rep (i, k+1) {
        ans = max(ans, max(dp[0][i], dp[1][i]) + max(dp[2][k-i], dp[3][k-i]));
    }
    cout << ans << endl;
}
