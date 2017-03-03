#include <iostream>
#include <string>
#include <ctype.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
using namespace std;

int main(){
    registerValidation();
    int n = inf.readInt(MIN_N, MAX_N);
    inf.readEoln();

    int string_length_sum = 0;
    string regex = "[a-z]*";

    for(int i = 0; i < n; i++){
        string s = inf.readToken(regex);
        inf.readEoln();
        string_length_sum += s.size();
    }
    assert(string_length_sum <= MAX_SUM_LEN);
    inf.readEof();
}
