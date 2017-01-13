#include <iostream>
#include <iomanip>
#include <utility>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);i++)

// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)
void output(double a, double b, const string &prefix, int num){
    char name[100];
    sprintf(name, "%s_%02d.in", prefix.c_str(), num);
    ofstream ofs(name);
    ofs << fixed << setprecision(10) << a << " " << b << endl;
    ofs.close();
}

int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
    rnd.setSeed(time(0)+getpid());

    // 乱数ケースを10個生成
    for(int i = 0; i < 10; ++i){
        double A = rnd.next(MIN_A, MAX_A);
        double B = rnd.next(MIN_B, MAX_B);
        output(A, B, "50_random", i);
    }
}
