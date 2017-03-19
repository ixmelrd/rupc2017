#include <iostream>
using namespace std;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n)-1;i>=0;i--)
#define rrep2(i,a,b) for (int i=(a)-1;i>=b;i--)
#define chmin(a,b) (a)=min((a),(b));
#define chmax(a,b) (a)=max((a),(b));
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define printV(v) cerr<<(#v)<<":";for(auto(x):(v)){cerr<<" "<<(x);}cerr<<endl;
#define printVS(vs) cerr<<(#vs)<<":"<<endl;for(auto(s):(vs)){cerr<<(s)<< endl;}
#define printVV(vv) cerr<<(#vv)<<":"<<endl;for(auto(v):(vv)){for(auto(x):(v)){cerr<<" "<<(x);}cerr<<endl;}
#define printP(p) cerr<<(#p)<<(p).first<<" "<<(p).second<<endl;
#define printVP(vp) cerr<<(#vp)<<":"<<endl;for(auto(p):(vp)){cerr<<(p).first<<" "<<(p).second<<endl;}

inline void output(){ cerr << endl; }
template<typename First, typename... Rest>
inline void output(const First& first, const Rest&... rest) {
    cerr << first << " "; output(rest...);
}

using ll = long long;
using Pii = pair<int, int>;
using TUPLE = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int inf = 1ll << 60;
const int mod = 1e9 + 7;
using Graph = vector<vector<int>>;

const int MAX = 100010;
double prob_pow[MAX]; // prob_pow[i] = p^i

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	prob_pow[0] = 1;
	cin >> prob_pow[1];
	rep2(i, 2, MAX - 1) prob[i + 1] = prob[i] * prob[1];
	int n;
	cin >> n;
	
}
