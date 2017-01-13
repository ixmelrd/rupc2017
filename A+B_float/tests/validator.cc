#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    inf.readDouble(MIN_A, MAX_A);
    inf.readSpace();
    inf.readDouble(MIN_B, MAX_B);
    inf.readEoln();
    inf.readEof();
}
