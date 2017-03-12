#include "testlib.h"
using namespace std;

const double ABS_DELTA = 1e-6;
const double REL_DELTA = 1e-6;
const double TOL = 1e-9;

int main(int argc, char * argv[])
{
    setName("diff");
    registerTestlibCmd(argc, argv);
    int n = 0;
    double a = ans.readDouble();
    double b = ouf.readDouble();
    ans.readEoln();
    ouf.readEoln();
    
    ans.readEof();
    ouf.readEof();
    

    if(abs(a-b)<=ABS_DELTA + TOL){
        quitf(_ok, "ABS_OK");   
    }
    if(b!=0 && abs((a-b)/b) <= REL_DELTA + TOL) {
        quitf(_ok, "REL");
    }
    quitf(_wa, "bad");
}