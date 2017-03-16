#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

const int INF = 1e9;

string s;
int k;

int main() {
    cin >> s >> k;
    int ans = -INF;
    int n = s.size();
    assert(n <= 10);
    int popcnt[1 << 10] = {};
    rep(i, 1 << 10) popcnt[i] = popcnt[i/2] + i%2;
    if (n == 1) {
        ans = 1;
    } else {
        rep(S, 1 << n) rep(T, 1 << n) {
            if (popcnt[S] + popcnt[T] > k) continue;
            int cx = 0, cy = 0;
            int ax = +1, ay = +1;
            rep(i, n) {
                if (S >> i & 1) ax *= -1;
                if (T >> i & 1) ay *= -1;
                int dx = 0, dy = 0;
                if (s[i] == 'U') dy = +1;
                if (s[i] == 'D') dy = -1;
                if (s[i] == 'R') dx = +1;
                if (s[i] == 'L') dx = -1;
                cx += dx * ax;
                cy += dy * ay;
            }
            int cand = abs(cx) + abs(cy);
            ans = max(ans, cand);
        }
    }
    cout << ans << endl;
}
