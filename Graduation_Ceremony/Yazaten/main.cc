#include <iostream>
#include <map>
#include <cstring>
#include <vector>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define INF (1e9+1)

int main(){
    string s;
    int k;
    cin>>s>>k;
    
    static int dp[2][2][2001][2001];
    memset(dp,0,sizeof(dp));
    
    map<char,int> mp[2][2];
    mp[0][0]['U']= 0, mp[0][0]['D']= 0, mp[0][0]['R']=+1, mp[0][0]['L']=-1;
    mp[0][1]['U']= 0, mp[0][1]['D']= 0, mp[0][1]['R']=-1, mp[0][1]['L']=+1;
    mp[1][0]['U']=+1, mp[1][0]['D']=-1, mp[1][0]['R']= 0, mp[1][0]['L']= 0;
    mp[1][1]['U']=-1, mp[1][1]['D']=+1, mp[1][1]['R']= 0, mp[1][1]['L']= 0;
    
    
    rep(x_y,2){
        rep(pos_neg,2){
            for(int i=1;i<=s.size();i++){
                rep(j,k+1){
                    int sign = j%2 ? -1:1 ;
                    int add = mp[x_y][pos_neg][s[i-1]] * sign;
                    dp[x_y][pos_neg][i][j] = dp[x_y][pos_neg][i-1][j]+add;
                    if(j-1>=0) dp[x_y][pos_neg][i][j] = max(dp[x_y][pos_neg][i][j],dp[x_y][pos_neg][i-1][j-1]-add);
                }
            }
        }
    }
    
    vector<int> x(k+1),y(k+1);
    rep(i,k+1)  x[i] = max(abs(dp[0][0][s.size()][i]),abs(dp[0][1][s.size()][i]));
    rep(i,k)    x[i+1] = max(x[i+1],x[i]);
    
    rep(i,k+1)  y[i] = max(abs(dp[1][0][s.size()][i]),abs(dp[1][1][s.size()][i]));
    rep(i,k)    y[i+1] = max(y[i+1],y[i]);
    
    
    
    int ans = -INF;
    rep(i,k+1){
        ans = max(ans,x[i]+y[k-i]);
    }
    cout<<ans<<endl;
}