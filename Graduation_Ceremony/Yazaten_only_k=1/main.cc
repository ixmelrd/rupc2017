#include<iostream>
#include<cassert>
#include<vector>
#include<map>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define all(a)  (a).begin(),(a).end()
#define pb emplace_back
#define INF (1e9+1)
//#define INF (1LL<<59)

int main(){
    string s;
    int k;
    cin>>s>>k;
    assert(k==1);
    
    vector<pii> vp(s.size()+2,pii(0,0)),vpr(s.size()+2,pii(0,0));
    
    map<char,pii> mp;
    mp['U']=pii(0,1);
    mp['R']=pii(1,0);
    mp['D']=pii(0,-1);
    mp['L']=pii(-1,0);

    for(int i=1;i<=vp.size()-2;i++){
        pii bef =vp[i-1];
        bef.first+=mp[s[i-1]].first;
        bef.second+=mp[s[i-1]].second;
        vp[i] = bef;
    }

    for(int i=vpr.size()-2;i>=1;i--){
        pii bef =vpr[i+1];
        bef.first+=mp[s[i-1]].first;
        bef.second+=mp[s[i-1]].second;
        vpr[i] = bef;
    }
    
    int maxi = 0;
    rep(i,vp.size()){
        pii a = vp[i];
        a.first-=vpr[i+1].first;
        a.second-=vpr[i+1].second;
//        cout<<a.first<<" "<<a.second<<endl;
        maxi = max(maxi,abs(a.first)+abs(a.second));
    }
    cout<<maxi<<endl;
}