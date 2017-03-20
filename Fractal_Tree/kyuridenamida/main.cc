#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector< pair<int,int> > g[100010];
long double p;
int N;

long double dfs1(int x,int prv,long double prob,long double weight){
  long double ans = prob * weight;
  for(auto c : g[x] ){
    if( c.first != prv ) 
      ans += dfs1(c.first,x,prob*p,c.second);
  }
  return ans;
}

long double dfs2(int x,int prv,long double prob,long double weight, long double step1){
  long double ans = prob * weight;
  for(auto c : g[x] ){
    if( c.first != prv ) 
      ans += dfs2(c.first,x,prob*p,c.second, step1);
  }
  ans += prob * step1;
  return ans;
}


int main2(){

  cin >> p >> N;
  for(int i = 0 ; i < N - 1 ; i++){
    int a,b,c;
    cin >> a >> b >> c;
    --a,--b;
    g[a].push_back({b,c});
    g[b].push_back({a,c});
  }
  long double answer1 = dfs1(0,-1,1.0,0);
  long double answer2 = dfs2(0,-1,1.0,0,answer1);

  printf("%.10lf\n",(double)answer2);


}

int main() {
  static ll eord, enew;
  const int sz = 256*1024*1024;
  static unsigned char *p = (unsigned char*)malloc(sz);
  enew = ((ll)(p+sz-1) & ~0xff);
  __asm__ volatile("mov %%rsp, %0" : "=r"(eord));
  __asm__ volatile("mov %0, %%rsp" : : "r"(enew));
  main2();
  __asm__ volatile("mov %0, %%rsp" : : "r"(eord));
  return 0;
}
