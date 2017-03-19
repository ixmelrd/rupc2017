#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)

string genNextString(string s) {
	rrep(i, (int)s.size()) {
		s[i] = (s[i] - 'a' + 1) % 26 + 'a';
		if (s[i] != 'a') return s;
		if (i == 0 && s[i] == 'a') return 'a' + s;
	}
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int N;
	cin >> N;
	vector<string> vs(N);
	rep(i, N) cin >> vs[i];

	rep2(len, 1, 4 + 1) {
		set<string> st;
		rep(i, N) {
			rep(j, (int)vs[i].size() - len + 1) {
				st.insert(vs[i].substr(j, len));
			}
		}
		for (string t(len, 'a'); (int)t.size() == len; t = genNextString(t)) {
			if (!st.count(t)) {
				cout << t << endl;
				return 0;
			}
		}
	}
}
