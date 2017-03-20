#include<iostream>
#include<cstdio>
#include<vector>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
int main(){
	int n,m,q;
//	cin>>n>>m>>q;
	scanf("%d %d %d",&n,&m,&q);
	n*=m;
	vvi in(18,vi(n));
	rep(i,n){
		int a,b;
//		cin>>a>>b;
		scanf("%d %d",&a,&b);
		in[0][i]=a*m+b;
	}
	vi hu(q);
	rep(i,q){
		int a,b;
//		cin>>a>>b;
		scanf("%d %d",&a,&b);
		hu[i]=a*m+b;
	}
	rep(i,17)rep(j,n)in[i+1][j]=in[i][in[i][j]];

	int l=0,r=n;
	while(r-l>1){
		int h=(l+r)/2;

		vi now(n);
		rep(i,n)now[i]=i;
		rep(i,18)if(h&1<<i)rep(j,n)now[j]=in[i][now[j]];

		vi H(n);
		rep(i,q)H[now[hu[i]]]++;

		bool han=true;
		rep(i,n)if(H[i]>1)han=false;

		if(han)l=h;
		else r=h;
	}
	if(r==n)r=-1;
//	cout<<r<<endl;
	printf("%d\n",r);
}










