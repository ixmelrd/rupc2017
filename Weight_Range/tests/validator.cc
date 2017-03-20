#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    int n = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int m = inf.readInt(MIN_M, n);
    inf.readEoln();

    for(int i = 0; i < n; i++){
        if(i) inf.readSpace();
        inf.readInt(MIN_A, MAX_A);
    }
    inf.readEoln();
    inf.readEof();
}
