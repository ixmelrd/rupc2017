#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    inf.readInt(MIN_A, MAX_A);
    inf.readSpace();
    inf.readInt(MIN_B, MAX_B);
    inf.readEoln();
    inf.readEof();
}
