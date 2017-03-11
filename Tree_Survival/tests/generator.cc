#include <iostream>
#include <tuple>
#include <utility>
#include <cassert>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(c) begin(c), end(c)
#define dump(x) cerr << __LINE__ << ":\t" #x " = " << (x) << endl

using PR = pair<int,int>;
using TPL = tuple<int,int,int>;

const int INF = 1e9;

// ワーシャルフロイドが走る程度
const int SMALL_GRAPH_THRESHOLD = 700;

// ファイルストリームに出力する
void output(int N, int M, int T, const vector<TPL> &edges, const string &prefix, int suffix){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), suffix);
    ofstream ofs(name);
    ofs << N << ' ' << M << ' ' << T << '\n';
    rep (i, M) {
        int a, b, t;
        tie(a, b, t) = edges[i];
        ofs << a + 1 << ' ' << b + 1 << ' ' << t << '\n';
    }
    ofs.close();
}



int diameter(int N, const vector<PR> &edges) {
    assert(N <= 700);
    static int d[SMALL_GRAPH_THRESHOLD + 1][SMALL_GRAPH_THRESHOLD + 1];
    rep (i, N) rep (j, N) d[i][j] = (i == j) ? 0 : INF;
    for(auto &e : edges) {
        int u, v;
        tie(u, v) = e;
        d[u][v] = d[v][u] = 1;
    }
    rep (k, N) rep (i, N) rep (j, N) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    int maxi = 0;
    rep (i, N) rep(j, N) {
        maxi = max(maxi, d[i][j]);
    }
    assert(maxi != INF);
    return maxi;
}

vector<PR> tree(int N) {
    vector<PR> edges;
    for (int i = 1; i < N; ++i) {
        int par = rnd.next(0, i - 1);
        edges.emplace_back(i, par);
    }
    return edges;
}

vector<PR> random_graph(int N, double p) {
    // ランダムに全域木を作り，残りの辺を確率 p で追加
    assert(N <= 700);
    vector<PR> edges = tree(N);
    rep (i, N) rep (j, i) {
        if (rnd.next(0.0, 1.0) < p) {
            edges.emplace_back(j, i);
        }
    }
    sort(all(edges));
    edges.erase(unique(all(edges)), edges.end());
    shuffle(all(edges));
    if ((int)edges.size() > MAX_M) {
        edges.resize(MAX_M);
    }
    return edges;
}

vector<PR> no_edge_graph(int n) {
    return {};
}

vector<TPL> random_t(const vector<PR> &edges, int T) {
    int M = edges.size();
    vector<TPL> res(M);
    rep (i, M) {
        int a, b;
        tie(a, b) = edges[i];
        int t = rnd.next(1, T);
        res[i] = make_tuple(a, b, t);
    }
    return res;
}

int main(){
    rnd.setSeed(time(0)+getpid());

    const int NUM_SR = 15;
    for(int i = 0; i < NUM_SR; ++i) {
        // 辺確率 p は[1e-8, 1.0]からlogをとって等間隔に選ぶ
        int N = rnd.next(MIN_N, SMALL_GRAPH_THRESHOLD);
        double p = exp(log(1e-8) + (log(1) - log(1e-8)) / NUM_SR * i);
        vector<PR> small_random = random_graph(N, p);
        // cerr << p << endl;
        // cerr << diameter(N, small_random) << endl;
        int T = rnd.next(MIN_T, MAX_T);
        vector<TPL> small_random_ = random_t(small_random, T);
        int M = small_random.size();
        output(N, M, T, small_random_, "50_random", i);
    }
}
