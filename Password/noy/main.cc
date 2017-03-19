#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<vector>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
const int INF = 2000000000;
using namespace std;

int N = 'z' - 'a' + 1;

int toDigit(string a){
    int res = 0;
    rep(i,a.size()){
        res *= N;
        res += a[i] - 'a' + 1;
    }
    return res;
}

int main(){
    int n;
    cin >> n;

    bool f[500000] = {0};
    string a;
    rep(i,n){
        cin >> a;
        int len = a.size();
        range(j,1,5){
            rep(k,len){
                if(j + k >= len){
                    f[toDigit(a.substr(k,len - k))] = true;
                }else{
                    f[toDigit(a.substr(k,j))] = true;;
                }
            }
        }
    }

    for(int i = 1; true; i++){
        if(not f[i]){
            string res = "";
            while(true){
                i--;
                res += 'a' + i % N;
                i/=N;
                if(i == 0) break;
            }
            reverse(all(res));
            cout << res << endl;
            return 0;
        }
    }
    return 0;
}
