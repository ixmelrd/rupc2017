#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <cassert>

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

    // 乱数ケース
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, N);
        vector<int> A = gen(N);
        output(N, M, A, "50_random", i);
    }

    // 色の数Nが少ない乱数ケース
    for(int i = 0; i < 10; ++i){
        int N = rnd.next(MIN_N, 10);
        int M = rnd.next(MIN_M, N);
        vector<int> A = gen(N);
        output(N, M, A, "51_random_Nsmall", i);
    }

    // 最大( LCM(N,M)が大きく、数の範囲の総和も大きい )ケース
    vector<int> primenums;
    const auto isPrime = [](int n){
        if(n<=1)return false;
        for(int i=2;i*i<=n;i++){
            if(n%i==0)return false;
        }
        return true;
    };
    for(int i=900;i<=1000;i++){
        if(isPrime(i)){
            primenums.push_back(i);
        }
    }

    for(int i = 0; i < 10; ++i){
        int pos = rnd.next(1,(int)primenums.size()-1);
        int N = primenums[ pos ];
        int M = primenums[ rnd.next(0,pos-1) ];
        assert(M<=N);
        vector<int> A(N);
        for(int j=0;j<N;j++){
            if(j%2==0)A[j]=0;
            else A[j]=100;
        }
        output(N, M, A, "52_NMprime", i);
    }

}
