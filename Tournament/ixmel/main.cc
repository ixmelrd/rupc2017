#include<iostream>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
using namespace std;
int main(){
	int n,m,gomi;
	cin>>n>>m;
	rep(i,m)cin>>gomi;
	cout<<n-m-1<<endl;
}






















