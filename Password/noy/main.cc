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

int convertTo27Decimal(string a){
    int res = 0;
    rep(i,a.size()){
        res *= N;
        res += a[i] - 'a' + 1;
    }
    return res;
}

string convertToString(int a){
    string res = "";
    int k = N;
    while(true){
        a--;
        res += 'a' + a % k;
        a/=N;
        if(a == 0) break;
    }
    reverse(all(res));
    return res;
}

string findPassword(set<int> s){
    int i = 1;
    auto it = s.begin();
    while(true){
        if(i != *it){
            return convertToString(i);
        }
        i++;
        it++;
    }
    return "error";
}

inline void partialStringToMap(map<string, bool> &m, string a){
    range(j,1,5){
        rep(k,a.size()){
            if(j + k >= a.size()){
                m[a.substr(k,a.size() - k)] = true;
            }else{
                m[a.substr(k,j)] = true;
            }
        }
    }
}

int main(){
    cin >> n;

    map<string, bool> m;
    rep(i,n){
        string a;
        cin >> a;
        partialStringToMap(m,a);
    }

    set<int> s;
    for(auto it:m) s.insert(convertTo27Decimal(it.first));
    cout << findPassword(s) << endl;

    return 0;
}
