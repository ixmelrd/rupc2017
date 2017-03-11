#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();

    int n = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int m = inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
    inf.readInt(MIN_R, MAX_R);
    inf.readSpace();
    int q = inf.readInt(MIN_Q, MAX_Q);
    inf.readEoln();

    for(int i = 0; i < m; i++){
        int a = inf.readInt(MIN_a_b, n);
        inf.readSpace();
        int b = inf.readInt(MIN_a_b, n);
        inf.readSpace();
        inf.readInt(MIN_c, MAX_c);
        inf.readEoln();

        assert(a != b);
    }

    for(int i = 0; i < q; i++){
        inf.readInt(MIN_x_y, n);
        inf.readSpace();
        inf.readInt(MIN_x_y, n);
        inf.readSpace();
        inf.readInt(MIN_z, MAX_z);
        inf.readEoln();
    }

    inf.readEof();
}
