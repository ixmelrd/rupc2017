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

int n;
int N = 'z' - 'a' + 1;



int main(){
    cin >> n;

    set<string> m;
    string a;
    rep(i,n){
        cin >> a;
        range(j,1,5){
            rep(k,a.size()){
                if(j + k >= a.size()){
                    m.insert(a.substr(k,a.size() - k));
                }else{
                    m.insert(a.substr(k,j));
                }
            }
        }
    }

    set<int> s;
    for(auto it:m) {
        int res = 0;
        rep(i,it.size()){
            res *= N;
            res += it[i] - 'a' + 1;
        }
        s.insert(res);
    }


    int i = 1;
    auto it = s.begin();
    while(true){
        if(i != *it){
            string res = "";
            int k = N;
            while(true){
                i--;
                res += 'a' + i % k;
                i/=N;
                if(i == 0) break;
            }
            reverse(all(res));
            cout << res << endl;
            return 0;
        }
        i++;
        it++;
    }
    return 0;
}
