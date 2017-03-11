#include<iostream>
#include<algorithm>
#include<string>
#include<map>
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

void allPartialStringTo27Decimal(vector<int> &num, map<string, int> m){
    for(auto it:m) num.emplace_back(convertTo27Decimal(it.first));
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

string findPassword(vector<int> num){
    int i = 1;
    while(true){
        if(i != num[i - 1]){
            return convertToString(i);
        }
        i++;
    }
    return "error";
}

vector<string> findPartialString(string a){
    vector<string> ret;
    range(i,1,5){
        rep(j,a.size()){
            if(j + i >= a.size()){
                ret.emplace_back(a.substr(j,a.size() - j));
            }else{
                ret.emplace_back(a.substr(j,i));
            }
        }
    }
    return ret;
}

void allPartialStringToMap(vector<string> v, map<string, int> &m){
    rep(i,n){
        vector<string> tmp;
        tmp = findPartialString(v[i]);
        rep(j,tmp.size()) m[tmp[j]] = 1;
    }
}

void inputString(vector<string> &v){
    rep(i,n) cin >> v[i];
}


int main(){
    cin >> n;

    vector<string> v(n);
    inputString(v);

    map<string, int> m;
    allPartialStringToMap(v,m);

    vector<int> num;
    allPartialStringTo27Decimal(num,m);
    sort(all(num));

    cout << findPassword(num) << endl;

    return 0;
}
