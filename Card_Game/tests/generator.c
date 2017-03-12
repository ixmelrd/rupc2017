//結構頑張ったんですがかなり重く、生成に数十秒かかってしまいます

#include <iostream>
#include <utility>
#include <cassert>
#include <algorithm>
#include <set>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)
typedef pair<int,int> pii;

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int N, int M, int R, int Q, 
            vector<int> A, vector<int> B, vector<int> C, 
            vector<int> X, vector<int> Y, vector<int> Z
            , const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs<<N<<" "<<M<<" "<<R<<" "<<Q<<endl;
    
    assert(A.size()==M);
    assert(B.size()==M);
    assert(C.size()==M);
    for(int i=0;i<M;i++){
        ofs<<A[i]<<" "<<B[i]<<" "<<C[i]<<endl;
    }

    assert(X.size()==Q);
    assert(Y.size()==Q);
    assert(X.size()==Q);
    for(int i=0;i<Q;i++){
        ofs<<X[i]<<" "<<Y[i]<<" "<<X[i]<<endl;
    }
    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 乱数ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,(int)min<long long int>(MAX_M,(long long int)(N)*(N-1)));
        int R = rnd.next(MIN_R,MAX_R);
        int Q = rnd.next(MIN_Q,MAX_Q);

        vector<int> A(M),B(M),C(M);
        if(N<=1000000/(N-1)){
            vector<pii> v;
            for(int i=1;i<=N;i++){
              for(int j=1;j<=N;j++){
                if(i==j)continue;
                v.push_back(pii(i,j));
              }
            }
            shuffle(v.begin(),v.end());
            rep(i,M){
              A[i] = v[i].first;
              B[i] = v[i].second;
              C[i] = rnd.next(MIN_c,MAX_c);
            }
        }else{
          set<pii> st;
          for(int i=0;i<M;i++){
            while(1){
              A[i] = rnd.next(MIN_a_b,N);
          
              int tmp_b = rnd.next(MIN_a_b,N);
              while(A[i]==tmp_b){
                tmp_b = rnd.next(MIN_a_b,N);
              }
              B[i] = tmp_b;
              if(st.count(pii(A[i],B[i]))==0)break;
            }
            st.insert(pii(A[i],B[i]));

            C[i] = rnd.next(MIN_c,MAX_c);
          }
        }

        vector<int> X(Q),Y(Q),Z(Q);
        for(int i=0;i<Q;i++){
          X[i] = rnd.next(MIN_x_y,N);
          Y[i] = rnd.next(MIN_x_y,N);
          Z[i] = rnd.next(MIN_z,MAX_z);
        }

        output(N, M, R, Q, A, B, C, X, Y, Z, "50_random", case_num);
    }


    // ゲーム回数Qの小さいケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,(int)min<long long int>(MAX_M,(long long int)(N)*(N-1)));
        int R = rnd.next(MIN_R,MAX_R);
        int Q = rnd.next(MIN_Q,MIN_Q+2);

        vector<int> A(M),B(M),C(M);
        if(N<=1000000/(N-1)){
            vector<pii> v;
            for(int i=1;i<=N;i++){
              for(int j=1;j<=N;j++){
                if(i==j)continue;
                v.push_back(pii(i,j));
              }
            }
            shuffle(v.begin(),v.end());
            rep(i,M){
              A[i] = v[i].first;
              B[i] = v[i].second;
              C[i] = rnd.next(MIN_c,MAX_c);
            }
        }else{
          set<pii> st;
          for(int i=0;i<M;i++){
            while(1){
              A[i] = rnd.next(MIN_a_b,N);
          
              int tmp_b = rnd.next(MIN_a_b,N);
              while(A[i]==tmp_b){
                tmp_b = rnd.next(MIN_a_b,N);
              }
              B[i] = tmp_b;
              if(st.count(pii(A[i],B[i]))==0)break;
            }
            st.insert(pii(A[i],B[i]));

            C[i] = rnd.next(MIN_c,MAX_c);
          }
        }

        vector<int> X(Q),Y(Q),Z(Q);
        for(int i=0;i<Q;i++){
          X[i] = rnd.next(MIN_x_y,N);
          Y[i] = rnd.next(MIN_x_y,N);
          Z[i] = rnd.next(MIN_z,MAX_z);
        }

        output(N, M, R, Q, A, B, C, X, Y, Z, "51_Qsmall", case_num);
    }


    // 交換を行わない(一致報酬が低く、交換コストが高い)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,(int)min<long long int>(MAX_M,(long long int)(N)*(N-1)));
        int R = rnd.next(MIN_R,MAX_R);
        int Q = rnd.next(MIN_Q,MAX_Q);

        vector<int> A(M),B(M),C(M);
        if(N<=1000000/(N-1)){
            vector<pii> v;
            for(int i=1;i<=N;i++){
              for(int j=1;j<=N;j++){
                if(i==j)continue;
                v.push_back(pii(i,j));
              }
            }
            shuffle(v.begin(),v.end());
            rep(i,M){
              A[i] = v[i].first;
              B[i] = v[i].second;
              C[i] = rnd.next(MAX_c/2,MAX_c);
            }
        }else{
          set<pii> st;
          for(int i=0;i<M;i++){
            while(1){
              A[i] = rnd.next(MIN_a_b,N);
          
              int tmp_b = rnd.next(MIN_a_b,N);
              while(A[i]==tmp_b){
                tmp_b = rnd.next(MIN_a_b,N);
              }
              B[i] = tmp_b;
              if(st.count(pii(A[i],B[i]))==0)break;
            }
            st.insert(pii(A[i],B[i]));

            C[i] = rnd.next(MIN_c,MAX_c);
          }
        }

        vector<int> X(Q),Y(Q),Z(Q);
        for(int i=0;i<Q;i++){
          X[i] = rnd.next(MIN_x_y,N);
          Y[i] = rnd.next(MIN_x_y,N);
          Z[i] = rnd.next(MIN_z,min(MIN_z+5,MAX_z));
        }

        output(N, M, R, Q, A, B, C, X, Y, Z, "52_NoneSwap", case_num);
    }


    // 交換が行われるである(一致報酬が高く、交換報酬が低い)ケースを10個生成
    for(int case_num = 0; case_num < 10; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,(int)min<long long int>(MAX_M,(long long int)(N)*(N-1)));
        int R = rnd.next(MIN_R,MAX_R);
        int Q = rnd.next(MIN_Q,MAX_Q);

        vector<int> A(M),B(M),C(M);
        if(N<=1000000/(N-1)){
            vector<pii> v;
            for(int i=1;i<=N;i++){
              for(int j=1;j<=N;j++){
                if(i==j)continue;
                v.push_back(pii(i,j));
              }
            }
            shuffle(v.begin(),v.end());
            rep(i,M){
              A[i] = v[i].first;
              B[i] = v[i].second;
              C[i] = rnd.next(MIN_c,min(MIN_c+2,MAX_c));
            }
        }else{
          set<pii> st;
          for(int i=0;i<M;i++){
            while(1){
              A[i] = rnd.next(MIN_a_b,N);
          
              int tmp_b = rnd.next(MIN_a_b,N);
              while(A[i]==tmp_b){
                tmp_b = rnd.next(MIN_a_b,N);
              }
              B[i] = tmp_b;
              if(st.count(pii(A[i],B[i]))==0)break;
            }
            st.insert(pii(A[i],B[i]));

            C[i] = rnd.next(MIN_c,MAX_c);
          }
        }

        vector<int> X(Q),Y(Q),Z(Q);
        for(int i=0;i<Q;i++){
          X[i] = rnd.next(MIN_x_y,N);
          Y[i] = rnd.next(MIN_x_y,N);
          Z[i] = rnd.next(MAX_z/2,MAX_z);
        }

        output(N, M, R, Q, A, B, C, X, Y, Z, "53_ManySwap", case_num);
    }


    // Rの値が2~10のケースを1個づつ生成
    for(int case_num = 0; case_num < 9; ++case_num){
        int N = rnd.next(MIN_N,MAX_N);
        int M = rnd.next(MIN_M,(int)min<long long int>(MAX_M,(long long int)(N)*(N-1)));
        int R = case_num+2;
        int Q = rnd.next(MIN_Q,MAX_Q);

        vector<int> A(M),B(M),C(M);
        if(N<=1000000/(N-1)){
            vector<pii> v;
            for(int i=1;i<=N;i++){
              for(int j=1;j<=N;j++){
                if(i==j)continue;
                v.push_back(pii(i,j));
              }
            }
            shuffle(v.begin(),v.end());
            rep(i,M){
              A[i] = v[i].first;
              B[i] = v[i].second;
              C[i] = rnd.next(MIN_c,MAX_c);
            }
        }else{
          set<pii> st;
          for(int i=0;i<M;i++){
            while(1){
              A[i] = rnd.next(MIN_a_b,N);
          
              int tmp_b = rnd.next(MIN_a_b,N);
              while(A[i]==tmp_b){
                tmp_b = rnd.next(MIN_a_b,N);
              }
              B[i] = tmp_b;
              if(st.count(pii(A[i],B[i]))==0)break;
            }
            st.insert(pii(A[i],B[i]));

            C[i] = rnd.next(MIN_c,MAX_c);
          }
        }

        vector<int> X(Q),Y(Q),Z(Q);
        for(int i=0;i<Q;i++){
          X[i] = rnd.next(MIN_x_y,N);
          Y[i] = rnd.next(MIN_x_y,N);
          Z[i] = rnd.next(MIN_z,MAX_z);
        }

        output(N, M, R, Q, A, B, C, X, Y, Z, "54_eachRvalue", case_num);
    }
}