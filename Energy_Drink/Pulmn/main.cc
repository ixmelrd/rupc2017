#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> P;
typedef pair<int,P> pip;
typedef vector<pip> vip;

const int inf=1<<30;

int n;

int main(){
	cin>>n;
	vip a(2*n);
	for(int i=0;i<n;i++){
		int A,B;
		cin>>A>>B;
		a[i]={A,{B,0}};
		a[i+n]={B,{A,1}};
	}
	sort(a.begin(),a.end(),[](pip p,pip q){
		if(p.first==q.first) return p.second>q.second;
		return p.first<q.first;
	});
	vi dp(2*n,inf);
	for(int i=0;i<2*n;i++){
		int x=a[i].second.first,b=a[i].second.second;
		auto it=lower_bound(dp.begin(),dp.end(),x);
		if((it-dp.begin())%2==b) *it=x;
	}
	cout<<lower_bound(dp.begin(),dp.end(),inf)-dp.begin()<<endl;
}