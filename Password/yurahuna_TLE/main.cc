#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)

// TLE解法
// 文字を長さ→辞書順の順で生成して毎回 string::find

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

	string s = "a";
	for (;;s = genNextString(s)) {
		bool found = false;
		rep(i, N) {
			if (vs[i].find(s) != string::npos) {
				found = true;
				break;
			}
		}
		if (!found) {
			cout << s << endl;
			return 0;
		}
	}
}
