#include <iostream>
#include <cstring>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)

// 誤解法
// 各マスに初めて訪れる時刻さえ異なれば -1 と判定
// O(HW)

const int MAX = 250010;
int nxt[MAX]; // nxt[i] = マス i の次のマス
int vis[MAX]; // vis[i] = マス i が最初に訪れられる時刻

int H, W, N;

// マス pos に step 回目のジャンプで訪れたとき，
// 今後誰かと衝突するなら衝突までのジャンプ回数を，そうでなければ -1 を返す
int collide(int pos, int step) {
	if (vis[pos] != -1) {
		return vis[pos] == step ? step : -1;
	}
	vis[pos] = step;
	return collide(nxt[pos], step + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	cin >> H >> W >> N;
	rep(j, H * W) {
		int r, c;
		cin >> r >> c;
		nxt[j] = r * W + c;
	}

	memset(vis, -1, sizeof(vis));

	rep(i, N) {
		int r, c;
		cin >> r >> c;
		int k = collide(r * W + c, 0);
		if (k != -1) {
			cout << k << endl;
			return 0;
		}
	}

	cout << -1 << endl;
}
