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
struct edge{
	int to,cap,cost,rev;
};
typedef vector<edge> ve;
typedef vector<ve> vve;
class MCF{	//Minimum Cost Flow
	public:
	int n;
	vve G;
	vi h,dist,prev,pree;
	MCF(int size){
		n=size;
		G=vve(n);
		h=dist=prev=pree=vi(n);
	}
	void add_edge(int s,int t,int ca,int co){
		edge e={t,ca,co,G[t].size()};
		G[s].pb(e);
		edge ee={s,0,-co,G[s].size()-1};
		G[t].pb(ee);
	}
	int mcf(int s,int t,int f){
		int out=0;
		h=vi(n);
		while(f>0){			
			priority_queue<pii,vector<pii> >q;
			dist=vi(n,inf);
			dist[s]=0;
			q.push(pii(0,s));
			while(!q.empty()){
				pii p=q.top();q.pop();
				int v=p.second;
				if(dist[v]<-p.first)continue;
				rep(i,G[v].size()){
					edge &e=G[v][i];
					if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
						dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
						prev[e.to]=v;
						pree[e.to]=i;
						q.push(pii(-dist[e.to],e.to));
					}
				}
			}
			if(dist[t]==inf)return -1;
			rep(i,n)h[i]+=dist[i];
			int d=f;
			for(int v=t;v!=s;v=prev[v])d=min(d,G[prev[v]][pree[v]].cap);
			f-=d;
			out+=d*h[t];
			for(int v=t;v!=s;v=prev[v]){
				edge &e=G[prev[v]][pree[v]];
				e.cap-=d;
				G[v][e.rev].cap+=d;
			}
		}
		return out;	
	}
};
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	vi a(n);
	rep(i,n)cin>>a[i];
	vvi b(m,vi(n));
	rep(i,m)rep(j,n)cin>>b[i][j];
	vi t(m);
	rep(i,m)cin>>t[i];
	
	MCF mcf(n+m+4);//toi hito sosu sink friend aor
	
	rep(i,n)mcf.add_edge(n+m,i,1,0);
	rep(i,n)mcf.add_edge(i,n+m+3,1,100-a[i]);
	rep(i,n)rep(j,m)
		mcf.add_edge(i,n+j,1,100-b[j][i]);
	rep(i,m)mcf.add_edge(n+i,n+m+2,t[i],0);
	mcf.add_edge(n+m+3,n+m+1,n,0);
	mcf.add_edge(n+m+2,n+m+1,n-k,0);
	
	int score=n*100-mcf.mcf(n+m,n+m+1,n);
	cout<<score<<" ";
	if(score>=n*90)cout<<"A"<<endl;
	else if(score>=n*70)cout<<"B"<<endl;
	else if(score>=n*50)cout<<"C"<<endl;
	else cout<<"F"<<endl;
	
}










