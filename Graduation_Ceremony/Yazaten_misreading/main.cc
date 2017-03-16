#include <iostream>
#include <map>
#include <cstring>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define INF (1e9+1)

int main(){
    string s;
    int k;
    cin>>s>>k;
    
    //q: quadrant
    static int dp[4][2001][2001];
    memset(dp,0,sizeof(dp));
    
    map<char,int> mp[4];
    mp[0]['U']=+1, mp[0]['R']=+1, mp[0]['D']=-1, mp[0]['L']=-1;
    mp[1]['U']=+1, mp[1]['R']=-1, mp[1]['D']=-1, mp[1]['L']=+1;
    mp[2]['U']=-1, mp[2]['R']=-1, mp[2]['D']=+1, mp[2]['L']=+1;
    mp[3]['U']=-1, mp[3]['R']=+1, mp[3]['D']=+1, mp[3]['L']=-1;
    
    
    rep(q,4){
        for(int i=1;i<=s.size();i++){
            rep(j,k+1){
                int sign = j%2 ? -1:1 ;
                int add = mp[q][s[i-1]] * sign;
                dp[q][i][j] = dp[q][i-1][j]+add;
                if(j-1>=0) dp[q][i][j] = max(dp[q][i][j],dp[q][i-1][j-1]-add);
            }
        }
    }
    
    int ans = -INF;
    rep(q,4){
        rep(j,k+1){
            ans = max(ans,dp[q][s.size()][j]);
        }
    }
    cout<<ans<<endl;
}