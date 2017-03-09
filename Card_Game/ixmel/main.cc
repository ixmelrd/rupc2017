#include<iostream>
#include<vector>
#include<queue>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
const double inf=1e8;
class DIJ{
	public:
	struct edge{
		int to,cost;
	};
	vector<vector<edge> >G;
	int n,R;
	vvi d;//distance
	DIJ(int size,int mod){
		n=size;
		R=mod;
		G=vector<vector<edge> >(n);
		d=vvi(n,vi(R,inf));
	}
	void add_edge(int a,int b,int c){
		edge e={a,c};
		G[b].pb(e);
	}
	void dij(int r){
		priority_queue<pii>q;
		rep(i,n)if((i+1)%R==r){
			d[i][r]=0;
			q.push(pii(0,i));
		}
		while(!q.empty()){
			pii p=q.top();
			q.pop();
			int pos=p.second,cost=-p.first;
			if(cost>d[pos][r])continue;
			rep(i,G[pos].size()){
				edge e=G[pos][i];
				int to=e.to;
				int nowcost=cost+e.cost;
				if(nowcost<d[to][r]){
					d[to][r]=nowcost;
					q.push(pii(-d[to][r],to));
				}
			}
		}
	}
};
int main(){
	int n,m,r,q;
	ll out=0;
	cin>>n>>m>>r>>q;
	DIJ dij(n,r);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		a--;b--;
		dij.add_edge(a,b,c);
	}
	rep(i,r)dij.dij(i);
	rep(i,q){
		int a,b,c;
		cin>>a>>b>>c;
		int mi=c;
		rep(j,r)mi=min(mi,dij.d[a-1][j]+dij.d[b-1][j]);
		out+=c-mi;
	}
	cout<<out<<endl;
}






















