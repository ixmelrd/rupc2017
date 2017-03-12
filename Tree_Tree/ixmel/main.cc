#include<iostream>
#include<vector>
#include<iomanip>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
#define shosu(x) fixed<<setprecision(x)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vp;
typedef vector<vp> vvp;
typedef vector<double> vd;
double p,out,Bscore;
vvp aG,bG;
int n,m;
vi used;
vd P;
void Adfs(int a,int b){//now_node hukasa
	used[a]=true;
	rep(i,aG[a].size())if(used[aG[a][i].first]==0){
		int to=aG[a][i].first;
		out+=Bscore*P[b+1]+P[b+1]*2*aG[a][i].second;
		Adfs(to,b+1);
	}
}
void Bdfs(int a,int b){//now_node hukasa
	used[a]=true;
	rep(i,bG[a].size())if(used[bG[a][i].first]==0){
		int to=bG[a][i].first;
		Bscore+=P[b+1]*2*bG[a][i].second;
		Bdfs(to,b+1);
	}
}
int main(){
	cin>>p;
	P=vd(100010);
	P[0]=1;
	rep(i,100009)P[i+1]=P[i]*p;
	cin>>n;
	aG=vvp(n);
	rep(i,n-1){
		int a,b,c;cin>>a>>b>>c;
		a--;b--;
		aG[a].pb(pii(b,c));
		aG[b].pb(pii(a,c));
	}
	m = n;
	bG=aG;
	/*cin>>m;
	bG=vvp(m);
	rep(i,m-1){
		int a,b,c;cin>>a>>b>>c;
		a--;b--;
		bG[a].pb(pii(b,c));
		bG[b].pb(pii(a,c));
	}
	*/

	used=vi(m);
	Bdfs(0,0);
	used=vi(n);
	Adfs(0,0);
	cout<<shosu(9)<<(out+Bscore) / 2.0 <<endl;
}






















