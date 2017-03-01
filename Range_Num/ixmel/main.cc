#include<iostream>
#include<vector>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
using namespace std;
typedef vector<int> vi;
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










