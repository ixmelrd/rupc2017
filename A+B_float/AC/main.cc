#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int n;
    cin >> n;
    srand(time(0));
    double a, b;
    cin >> a >> b;
    cout << fixed << setprecision(10) << a+b << endl;
}
