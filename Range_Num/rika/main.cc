#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for(i=0;i<n;i++)
int main(void) {
    int n,m,i;
    cin>>n>>m;
    vector<int> a(n);
    rep(i,n)cin>>a[i];
    int ans=0;
    int now=0;
    while(1){
        int l=0,s=100;
        rep(i,m){
            l=max(l,a[(now+i)%n]);
            s=min(s,a[(now+i)%n]);
        }
        ans+=l-s;
        now+=i;
        if(now%n==0)break;
    }
    cout<<ans<<endl;
}

