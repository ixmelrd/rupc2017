#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define RFOR(i, a, b) for (int i = (b)-1; i >= int(a); --i)
#define rep(i, n) FOR(i, 0, n)
#define rep1(i, n) FOR(i, 1, int(n) + 1)
#define rrep(i, n) RFOR(i, 0, n)
#define rrep1(i, n) RFOR(i, 1, int(n) + 1)
#define all(c) begin(c), end(c)

bool used[600000];
char s[500010];

bool ok(int x){
    if (x == 0 || used[x]) return false;
    while (x != 0) {
        if (x % 27 == 0) return false;
        x /= 27;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int k = strlen(s);
        rep (i, k) {
            int x = 0;
            rep (l, 4) {
                if (i + l >= k) continue;
                x *= 27;
                x += s[i + l] - 'a' + 1;
                used[x] = true;
            }
        }
    }

    rep (i, 500000) if (ok(i)) {
        string s;
        int x = i;
        if (x == 0) s += 'a';
        else {
            while(x) {
                s += x % 27 + 'a' - 1;
                x /= 27;
            }
        }
        reverse(all(s));
        cout << s << endl;
        break;
    }
}
