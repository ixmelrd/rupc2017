#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int n;
    cin >> n;
    srand(time(0));
    double a, b;
    cin >> a >> b;
    // 制度不足
    cout << fixed << setprecision(1) << a+b << endl;
}
