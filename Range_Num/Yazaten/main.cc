#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define all(a)  (a).begin(),(a).end()
#define pb emplace_back

int main(){
    int N,M;
    cin>>N>>M;
    vector<int> A(N);
    rep(i,N)cin>>A[i];
    
    vector<int> v(N);    //v[i]: A[i]~A[i+M-1]までをグループにしたときの「数字の範囲」
    
    //v[i]を求めておく( O(N M logM) )
    rep(i,N){
        vector<int> tmp;
        for(int j=i;j<i+M;j++) tmp.pb( A[j%N] );
        
        sort(all(tmp));
        int maxi = tmp[tmp.size()-1];
        int mini = tmp[0];
        
        v[i] = maxi - mini;
    }
    
    int ans = 0;
    int lcm = N*M/__gcd(N,M);
    
    rep(i,lcm/M){   //作業は LCM(N,M)/M 回行われ、LCM(N,M)/M個のグループができる
        int index = (i*M)%N;
        ans+=v[index];
    }
    cout<<ans<<endl;
}
