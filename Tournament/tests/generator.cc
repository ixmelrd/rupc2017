#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <cassert>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, int M, vector<int> A, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << N << " " << M << endl;
    assert(M==A.size());
    for(int i=0;i<A.size();i++){
        ofs << A[i] << endl;
    }
    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    //乱数ケースを10個生成
    for(int case_num=0; case_num<20; ++case_num){
        int N = 1<<rnd.next(MIN_N_EXPORNENT,MAX_N_EXPORNENT);
        int M = rnd.next(MIN_M,N-1);
        vector<int> num(N);
        rep(i,N)num[i] = i;
        shuffle(num.begin(),num.end());
        vector<int> A(M);
        for(int j=0;j<M;j++){
            A[j] = num[j];
        }
        output(N, M, A, "50_random", case_num);
    }

    //Mの小さい乱数ケースを10個生成
    for(int case_num=0; case_num<10; ++case_num){
        int N = 1<<rnd.next(MIN_N_EXPORNENT,MAX_N_EXPORNENT);
        int M = rnd.next(MIN_M,min(MIN_M+3,N-1));
        vector<int> num(N);
        rep(i,N)num[i] = i;
        shuffle(num.begin(),num.end());
        vector<int> A(M);
        for(int j=0;j<M;j++){
            A[j] = num[j];
        }
        output(N, M, A, "51_random_Nsmall", case_num);
    }
    //Mの大きい乱数ケースを10個生成
    for(int case_num=0; case_num<10; ++case_num){
        int N = 1<<rnd.next(MIN_N_EXPORNENT,MAX_N_EXPORNENT);
        int M = rnd.next(max(MIN_M,N-4),N-1);
        vector<int> num(N);
        rep(i,N)num[i] = i;
        shuffle(num.begin(),num.end());
        vector<int> A(M);
        for(int j=0;j<M;j++){
            A[j] = num[j];
        }
        output(N, M, A, "52_random_Nlarge", case_num);
    }
}
