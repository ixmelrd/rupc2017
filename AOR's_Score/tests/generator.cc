#include <iostream>
#include <utility>
#include <cassert>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, int M, int K, vector<int> A, vector< vector<int> > B, vector<int> T, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs<<N<<" "<<M<<" "<<K<<endl;
    
    assert(A.size()==N);
    for(int i=0;i<N;i++){
        if(i)ofs<<" ";
        ofs<<A[i];
    }
    ofs<<endl;

    assert(B.size()==M);
    assert(B.size()==0 || B[0].size()==N);
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(j)ofs<<" ";
            ofs<<B[i][j];
        }
        ofs<<endl;
    }

    assert(T.size()==M);
    for(int i=0;i<M;i++){
        if(i)ofs<<" ";
        ofs<<T[i];
    }
    ofs<<endl;

    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 乱数ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = rnd.next(MIN_K,N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_random", case_num);
    }


    // 無限に友達を頼れる(k=0)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = 0;

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_CanRelyAnytime", case_num);
    }


    // 一度も友達を頼れない(k=N)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = N;

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_CannotRelyAnytime", case_num);
    }


    // 友だちがいない(M=0)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = 0;
        int K = rnd.next(MIN_K,N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_NoFriends", case_num);
    }


    // 友だちを頼る必要のない(Ai>=Bij)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = rnd.next(MIN_K,N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,A[j]);
                assert(B[i][j]<=MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_TENSAI", case_num);
    }


    // 全ての問題において友だちを頼ったほうがよい(Ai<=Bij)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = rnd.next(MIN_K,N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(A[j],MAX_B);
                assert(B[i][j]>=MIN_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_HISAI", case_num);
    }


    // 最大ケースを5個生成
    for(int case_num = 0; case_num < 5; ++case_num){
        int N = rnd.next(MAX_N-2,MAX_N);
        int M = rnd.next(MAX_M-2,MAX_M);
        int K = rnd.next(max(N-2,0),N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MAX_A-2,MAX_A);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B-2,MAX_B);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(max(N-2,0),N);
        }

        output(N, M, K, A, B, T, "50_maximum", case_num);
    }


    // 最小ケースを5個生成
    for(int case_num = 0; case_num < 5; ++case_num){
        int N = rnd.next(MIN_N,MIN_N+1);
        int M = rnd.next(MIN_M,MIN_M+1);
        int K = rnd.next(MIN_K,min(N,MIN_K+1));

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(MIN_A,MIN_A+1);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(MIN_B,MIN_B+1);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,min(N,MIN_T+1));
        }

        output(N, M, K, A, B, T, "50_minimum", case_num);
    }


    // Ai,Bij = {0,1}のケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,MAX_M);
        int K = rnd.next(MIN_K,N);

        vector<int> A(N);
        for(int i=0;i<N;i++){
            A[i] = rnd.next(0,1);
        }

        vector< vector<int> > B(M,vector<int>(N));
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                B[i][j] = rnd.next(0,1);
            }
        }

        vector<int> T(M);
        for(int i=0;i<M;i++){
            T[i] = rnd.next(MIN_T,N);
        }

        output(N, M, K, A, B, T, "50_ZeroOne", case_num);
    }
}
