#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    srand(time(0));
    int a = rand()%n;
    int b = n-a;
    cout << a << ' ' << b << endl;
}
