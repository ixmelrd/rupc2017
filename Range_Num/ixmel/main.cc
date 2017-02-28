#include<iostream>
#include<vector>
#include<string>
#include<algorithm>	
#include<map>
#include<set>
#include<utility>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<cstdio>
#include<sstream>
#include<iomanip>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
#define mp make_pair
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)
using namespace std;
//kaewasuretyuui
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vp;
typedef vector<vp> vvp;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<int,pii> pip;
typedef vector<pip>vip;
const double PI=acos(-1);
const double EPS=1e-9;
const int inf=1e8;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int main(){
	int n,m;
	cin>>n>>m;
	int sum=0;
	int now=0;
	vi in(n);
	rep(i,n)cin>>in[i];
	do{
		int mi=inf,ma=-inf;
		rep(i,m){
			int t=in[now];
			mi=min(mi,t);
			ma=max(ma,t);
			
			now++;
			if(now==n)now=0;
		}
		sum+=ma-mi;
	}while(now);
	cout<<sum<<endl;
}










