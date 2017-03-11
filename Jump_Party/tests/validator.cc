#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    int H = inf.readInt(MIN_H, MAX_H);
    inf.readSpace();
    int W = inf.readInt(MIN_W, MAX_W);
    inf.readSpace();
    int N = inf.readInt(MIN_N, MAX_N);
    inf.readEoln();

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            inf.readInt(0, H - 1);
            inf.readSpace();
            inf.readInt(0, W - 1);
            if (j == W - 1) inf.readEoln();
            else inf.readSpace();
        }
    }

    for (int i = 0; i < N; ++i) {
        inf.readInt(0, H - 1);
        inf.readSpace();
        inf.readInt(0, W - 1);
        inf.readEoln();
    }

    inf. readEof();
}
