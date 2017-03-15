#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

const int INF = 1e9;

string s;
int k;

void solve(const string &a, int dp[2010][2010]) {
    int n = s.size();
    rep (i, 2010) rep (j, 2010) dp[i][j] = -INF;
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (dp[i][j] == -INF) continue;
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            dp[i][j+1] = max(dp[i][j+1], dp[i][j]);
            int d = 1;
            if (a[i] == 'D' || a[i] == 'L') d *= -1;
            if (j % 2 == 1) d *= -1;
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + d);
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] - d);
        }
    }
}

int dpud[2010][2010], dplr[2010][2010];
int dpud2[2010][2010], dplr2[2010][2010];

int main() {
    cin >> s >> k;
    string ud, lr;
    string ud2, lr2;
    for (char c : s) {
        if (c == 'U' || c == 'D') {
            ud += c;
            ud2 += c ^ ('U' ^ 'D');
        }
        if (c == 'L' || c == 'R') {
            lr += c;
            lr2 += c ^ ('L' ^ 'R');
        }
    }
    int a = ud.size(), b = lr.size();
    solve(ud, dpud);
    solve(lr, dplr);
    solve(ud2, dpud2);
    solve(lr2, dplr2);
    int ans = -1e9;
    for (int i = 0; i <= k; ++i) {
        int cand = 0;
        cand += max(dpud[a][i], dpud2[a][i]);
        cand += max(dplr[b][i], dplr2[b][i]);
        ans = max(ans, cand);
    }
    cout << ans << endl;
}
