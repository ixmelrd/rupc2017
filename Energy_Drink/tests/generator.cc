#include <iostream>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <string>

using namespace std;

int a[MAX_N];
int b[MAX_N];
const int bufsize=100000;                                                                 
char buf[bufsize];

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(int n, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs.rdbuf()->pubsetbuf(buf, bufsize);

    ofs << n << "\n";
    for(int i = 0; i < n; ++i){
        ofs << a[i] << " " << b[i] << "\n";
    }
    ofs.close();
}

void randomCase(int min_n, int max_n, int min_a, int max_a, int min_b, int max_b, const string &prefix, int num){
    for(int i = 0; i < num; ++i){
        int N = rnd.next(min_n, max_n);
        for(int j = 0; j < N; ++j){
            a[j] = rnd.next(min_a, max_a);
            b[j] = rnd.next(min_b, max_b);
        }
        output(N, prefix.c_str(), i);
    }
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 小さめの乱数ケースを5個生成
    randomCase(MIN_N, 10, MIN_A, 10, MIN_B, 10, "50_random_min", 5);

    // 完全乱数ケースを10個生成
    randomCase(MIN_N, MAX_N, MIN_A, MAX_A, MIN_B, MAX_B, "51_random", 10);

    // N最大，大きめの乱数ケースを10個生成
    randomCase(MAX_N-1, MAX_N, MAX_A/2, MAX_A, MAX_B/2, MAX_B, "52_random_large", 10);

    // N最小ケースを5個生成
    randomCase(MIN_N, MIN_N, MIN_A, 10, MIN_B, 10, "53_random_min_n", 5);

    // 全部最大ケース
    randomCase(MAX_N, MAX_N, MAX_A, MAX_A, MAX_B, MAX_B, "54_maximum", 1);

    // a_1 == a_2 == b_1 == b_2 のケース
    for(int i = 0; i < 2; ++i){
        a[i] = 10;
        b[i] = 10;
    }
    output(2, "10_handmade", 0);

    // 日数最大のケース
    for(int i = 0; i < MAX_N; ++i){
        a[i] = MIN_A + i;
        b[i] = MIN_B + i;
    }
    output(MAX_N, "10_handmade", 1);

    // N最大，a+bがすべて等しいケース
    for(int i = 0; i < MAX_N; ++i){
        a[i] = MIN_A + (MAX_N - i - 1);
        b[i] = MIN_B + i;
    }
    output(MAX_N, "10_handmade", 2);
}
