#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int lcm(int a, int b) {
    return a / __gcd(a, b) * b;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int l = lcm(n, m);
    vector<int> v(l);
    rep(i, l) {
        v[i] = a[i % n];
    }

    int ans = 0;
    for (int i = 0; i < l; i += m) {
        int ma = -1;
        int mi = 101;
        rep(j, m) {
            ma = max(ma, v[i + j]);
            mi = min(mi, v[i + j]);
        }
        ans += ma - mi;
    }
    cout << ans << endl;
}
