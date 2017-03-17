#include<iostream>
#include<vector>
#include<algorithm>	
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
#define all(in) in.begin(),in.end()
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vp;
typedef pair<pii,pii> pip;
typedef vector<pip>vip;
const int inf=1e9;
int main(){
	int n,m,s,g,out=inf;
	cin>>n>>m>>s>>g;
	s--;g--;
	vp dp(n,pii(-inf,inf));
	dp[s]=pii(0,0);
	vi bas(m);
	vip in;
	rep(i,m){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		a--;b--;
		in.pb({{c,i},{0,a}});
		in.pb({{c+d,i},{1,b}});
	}
	sort(all(in));
//	rep(i,in.size())cout<<in[i].first<<" "<<in[i].second.first<<" "<<in[i].second.second<<endl;
	rep(i,in.size()){
		if(in[i].second.first==0){//hatu
			int now=in[i].second.second;
			if(now==g||dp[now]==pii(inf,inf))continue;
			bas[in[i].first.second]=in[i].first.first-dp[now].first+dp[now].second;
		}else{//tyaku
			int now=in[i].second.second,t=bas[in[i].first.second];
			if(now==g){
				out=min(out,t);
			}else{//tyaku
				if(in[i].first.first-dp[now].first>t-dp[now].second)dp[now]=pii(in[i].first.first,t);
			}
		}
	}
	cout<<out<<endl;
}
