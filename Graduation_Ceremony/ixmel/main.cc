#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
int n,k;
string s;
vi f(int c){
	vvi dp(2,vi(k+1));
	rep(i,n){
		int d=0;
		if(c==0&&s[i]=='U')d=1;
		if(c==0&&s[i]=='D')d=-1;
		if(c==1&&s[i]=='R')d=1;
		if(c==1&&s[i]=='L')d=-1;
		for(int j=k;j>=0;j--){
			if(j<k){
				int D=d;
				if(j%2==0)D*=-1;
				dp[0][j+1]=min(dp[0][j+1],dp[0][j]+D);
				dp[1][j+1]=max(dp[1][j+1],dp[1][j]+D);
			}
			int D=d;
			if(j%2)D*=-1;
			dp[0][j]+=D;//min(dp[0][j],dp[0][j]+D);
			dp[1][j]+=D;//max(dp[1][j],dp[1][j]+D);
			
		}
	}
	vi out(k+1);
	rep(i,k+1)out[i]=max(-dp[0][i],dp[1][i]);
	return out;
}
int main(){
	cin>>s>>k;
	n=s.size();
	vi a=f(0),b=f(1);
	int out=0;
	rep(i,k+1)rep(j,k+1)if(i+j<=k)out=max(out,a[i]+b[j]);
	cout<<out<<endl;
}








