#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    int n = inf.readInt();
    inf.readEoln();
    for(int i = 0; i < n; ++i){
        inf.readInt(MIN_A, MAX_A);
        inf.readSpace();
        inf.readInt(MIN_B, MAX_B);
        inf.readEoln();
    }
    inf.readEof();
}
