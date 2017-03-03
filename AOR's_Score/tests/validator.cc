#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

void readIntLine(int len, int min, int max){
    for(int i = 0; i < len; ++i){
        if(i > 0) inf.readSpace();
        inf.readInt(min, max);
    }
    inf.readEoln();
}

int main(){
    registerValidation();
    // read first line
    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
    inf.readInt(MIN_K, N);
    inf.readEoln();

    // read second line
    readIntLine(N, MIN_A, MAX_A);

    // read b
    for(int i = 0; i < M; ++i){
        readIntLine(N, MIN_B, MAX_B);
    }

    // read last line
    readIntLine(M, MIN_T, N);
    
    inf.readEof();
}
