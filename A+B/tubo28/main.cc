#include<iostream>
using namespace std;
int main(){
    // 遅いが間に合う別解
    int a, b;
    cin >> a >> b;
    int ans = 0;
    while(a != 0){
        --a;
        ++ans;
    }
    while(b != 0){
        --b;
        ++ans;
    }
    cout << ans << endl;
}
