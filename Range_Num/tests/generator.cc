#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

void output(int N, int M, const vector<int> &a, const string &prefix, int suffix){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), suffix);
    ofstream ofs(name);
    ofs << N << ' ' << M << endl;
    for (int i = 0; i < N; ++i) {
        ofs << a[i] << (i + 1 == N ? '\n' : ' ');
    }
    ofs.close();
}

vector<int> gen(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = rnd.next(MIN_A, MAX_A);
    }
    return A;
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 小さい乱数ケース
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, 10);
        int M = rnd.next(MIN_M, N);
        vector<int> A = gen(N);
        output(N, M, A, "50_random", i);
    }
    // 大きい乱数ケース
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, N);
        vector<int> A = gen(N);
        output(N, M, A, "50_random", i);
    }
}
