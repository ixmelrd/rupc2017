#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>

int main(){
    registerValidation();
    inf.readToken("[UDRL]{1,2000}");
    inf.readEoln();
    inf.readInt(MIN_K, MAX_K);
    inf.readEoln();
    inf.readEof();
}
