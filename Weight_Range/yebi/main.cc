#include<iostream>
#include<vector>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using namespace std;
#define MAX  999999
int main(){
    int N,M; cin>>N>>M;
    int ans=0,cnt=1;
    vector<int>v(N+1,0); rep(i,N)cin>>v[i+1];
    while(true){
        int maxi= -MAX, mini=MAX;
        for(int i=M*(cnt-1)+1;i<=cnt*M;i++){
            maxi=max(maxi,v[i%N ? i%N:N]);
            mini=min(mini,v[i%N ? i%N:N]);
        }
        ans+=maxi-mini;
        if(!((cnt*M)%N))break;
        cnt++;
    }
    cout<<ans<<endl;
}
