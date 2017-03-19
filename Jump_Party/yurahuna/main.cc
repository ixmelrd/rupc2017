#include <iostream>
#include <cstring>
using namespace std;
#define rep(i,n) for (int i=0;i<(n);i++)

// ダブリング + 二分探索
// O( HW * (log(HW))^2 )

const int MAX = 250010;
const int MAX_LOG = 20;
int nxt[MAX_LOG + 1][MAX];	// nxt[i][j]	= マス j から 2^i 回ジャンプして行き着くマス
int src[MAX];				// src[i]		= i 番目の人の初期位置

int H, W, N;

// マス j から k 回ジャンプして行き着くマスを求める
int dst(int j, int k) {
	for (int i = 0; k > 0; i++, k >>= 1) {
		if (k & 1) j = nxt[i][j];
	}
	return j;
}

// 全員が k 回ジャンプしたとき，衝突が起きていれば true, そうでなければ false を返す
bool collide(int k) {
	memset(used, false, sizeof(used));
	rep(i, N) {
		int dst_i = dst(src[i], k);
		if (used[dst_i]) return true;
		used[dst_i] = true;
	}
	return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	cin >> H >> W >> N;
	rep(j, H * W) {
		int r, c;
		cin >> r >> c;
		nxt[0][j] = r * W + c;
	}

	rep(i, N) {
		int r, c;
		cin >> r >> c;
		src[i] = r * W + c;
	}

	rep(i, MAX_LOG) {
		rep(j, H * W) {
			nxt[i + 1][j] = nxt[i][nxt[i][j]];
		}
	}

	int l = 0, r = 1 << MAX_LOG;
	while (r - l > 1) {
	    int m = (l + r) / 2;
	    (collide(m) ? r : l) = m;
	}
	cout << (r < H * W ? r : -1) << endl;
}
