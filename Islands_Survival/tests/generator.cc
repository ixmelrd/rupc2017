#include <iostream>
#include <set>
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

// ファイルストリームに出力する
void output(int N, int M, int T, const vector<TPL> &edges, const string &prefix, int suffix){
    assert((int)edges.size() == M);
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

vector<PR> tree(int N) {
    vector<PR> edges;
    for (int i = 1; i < N; ++i) {
        int par = rnd.next(0, i - 1);
        edges.emplace_back(i, par);
    }
    return edges;
}

vector<PR> star(int N) {
    int c = rnd.next(0, N - 1);
    vector<PR> edges;
    for (int i = 0; i < N; ++i) {
        if (i == c) continue;
        edges.emplace_back(c, i);
    }
    return edges;
}

vector<PR> add_edges_to_tree(int N, int M) {
    vector<PR> edges = tree(N);
    for (auto &e : edges) {
        if (e.first > e.second) swap(e.first, e.second);
    }
    set<PR> used(edges.begin(), edges.end());
    assert(M <= (long long)N*(N-1)/2);
    while((int)edges.size() != M) {
        int a = rnd.next(0, N - 1);
        int b = rnd.next(0, N - 1);
        if (a == b) continue;
        if (a > b) swap(a, b);
        if (used.count(PR(a, b))) continue;
        edges.emplace_back(a, b);
        used.emplace(a, b);
    }
    shuffle(all(edges));
    return edges;
}

vector<PR> path_graph(int N) {
    vector<PR> edges;
    rep (i, N - 1) {
        edges.emplace_back(i, i + 1);
    }
    return edges;
}

vector<PR> dango_graph() {
    const int SUPER_TREE_NODE = 90;
    const int DENCE_NODE = 50;
    const int DENCE_EDGE = 1000;
    assert(DENCE_NODE * SUPER_TREE_NODE <= MAX_N);
    assert(DENCE_NODE * DENCE_EDGE + (SUPER_TREE_NODE - 1) <= MAX_M);

    vector<PR> edges;

    for (int i = 0; i < SUPER_TREE_NODE; ++i) {
        vector<PR> dence = add_edges_to_tree(DENCE_NODE, DENCE_EDGE);
        for (auto &e : dence) {
            e.first += DENCE_NODE * i;
            e.second += DENCE_NODE * i;
        }
        edges.insert(edges.end(), all(dence));
    }

    vector<PR> tree = ::tree(SUPER_TREE_NODE);
    for (auto &e : tree) {
        int u, v;
        tie(u, v) = e;
        u = u*DENCE_NODE + rnd.next(0, DENCE_NODE - 1);
        v = v*DENCE_NODE + rnd.next(0, DENCE_NODE - 1);
        edges.emplace_back(u, v);
    }

    return edges;
}

vector<TPL> random_t(const vector<PR> &edges, int max_t) {
    int M = edges.size();
    vector<TPL> res(M);
    rep (i, M) {
        int a, b;
        tie(a, b) = edges[i];
        int t = rnd.next(1, max_t);
        res[i] = make_tuple(a, b, t);
    }
    return res;
}

vector<TPL> max_t(const vector<PR> &edges) {
    int M = edges.size();
    vector<TPL> res(M);
    rep (i, M) {
        int a, b;
        tie(a, b) = edges[i];
        res[i] = make_tuple(a, b, MAX_T);
    }
    return res;
}

int main(){
    rnd.setSeed(time(0)+getpid());

    // 木に適当に辺を追加
    // 手計算で確認用の小さいケース (意外とコーナーケースが生成されたりもする)
    for (int i = 0; i < 10; ++i) {
        int N = rnd.next(MIN_N, 5);
        int M = rnd.next(N - 1, N*(N - 1)/2);
        int T = 5;
        vector<TPL> g = random_t(add_edges_to_tree(N, M), T);
        output(N, M, T, g, "50_random_small", i);
    }

    for (int i = 0; i < 10; ++i) {
        int N = rnd.next(MIN_N, MAX_N);
        int M = min(MAX_M, N * (int)rnd.next(1.0, 1.1));
        int T = rnd.next(MIN_T, MAX_T);
        vector<TPL> g = random_t(add_edges_to_tree(N, M), T);
        output(N, M, T, g, "51_random_sparce", i);
    }

    for (int i = 0; i < 10; ++i) {
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(N - 1, (int)min((long long)MAX_M, (long long)N*(N - 1)/2));
        int T = rnd.next(MIN_T, MAX_T);
        vector<TPL> g = random_t(add_edges_to_tree(N, M), T);
        output(N, M, T, g, "52_random_dence", i);
    }

    // 木
    for (int i = 0; i < 4; ++i) {
        int N = rnd.next(MIN_N, MAX_N);
        int T = rnd.next(MIN_T, MAX_T);
        vector<TPL> t = random_t(tree(N), T);
        output(N, N - 1, T, t, "53_tree", i);
    }

    // スター
    for (int i = 0; i < 4; ++i) {
        int N = rnd.next(MIN_N, MAX_N);
        int T = rnd.next(MIN_T, MAX_T);
        vector<TPL> t = random_t(star(N), T);
        output(N, N - 1, T, t, "54_star", i);
    }

    // 大きい密な成分がたくさん
    for (int i = 0; i < 4; ++i) {
        int N = 4500;
        vector<TPL> g = random_t(dango_graph(), MAX_T);
        int M = g.size();
        int T = MAX_T;
        output(N, M, T, g, "55_dange", i);
    }

    // 長いパス (DFS殺し)
    {
        int N = MAX_N;
        vector<TPL> g = random_t(path_graph(N), MAX_T);
        output(N, N - 1, MAX_T, g, "56_dfs_killer", 0);
    }

    // オーバーフロー殺し
    {
        int N = MAX_N;
        int M = MAX_M;
        vector<TPL> g = max_t(add_edges_to_tree(N, M));
        output(N, M, MAX_T, g, "57_32bit_killer", 0);
    }
    
}
