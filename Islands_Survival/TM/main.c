#include<stdio.h>
int MAX(int a,int b){return a<b?b:a;}
int R=1,C=1,H[2000010],N[2000010];
//評価関数（いまはMIN）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]>N[H[b]]?1:0;
}
//挿入関数
void hin(int a){
  int i=C++;
  for(N[H[0]=R]=a;hyouka(0,i/2);i/=2)H[i]=H[i/2];
  H[i]=R++;
}
//取り出す関数
int hout(){
  int rt=H[1],i,j=2,k=H[--C];
  for(i=1;hyouka(i,C);i=j)H[i]=H[j=i*2+1-hyouka(i*2,i*2+1)];
  H[j/2]=k;
  return rt;
}
int p[100010]={0};
int d[100010]={0};
int ta[100010],to[200010],nt[200010],co[200010],f[200010];
int dp[100010],cc[100010],bt[100010],n,m;
int Find(int *a,int *b){
  int r,n;
  for(r=++(*a);p[r];r=p[r]);
  for(;n=p[*a];*a=n)p[*a]=r;
  for(r=++(*b);p[r];r=p[r]);
  for(;n=p[*b];*b=n)p[*b]=r;
  return *a-*b?1:0;
}
void Union(int id){
  int a=to[(id+m)%(2*m)],b=to[id],t,pa=0,pb=0,i;
  //printf("%d %d\n",a,b);
  if(Find(&a,&b)){
    if(d[a]<d[b]){
      t=a;
      a=b;
      b=t;
    }
    p[b]=a;
    if(d[a]=d[b])d[a]++;
    if(f[a-1]+1)pa=dp[a]+cc[a]*(bt[a]-co[id]);
    if(f[b-1]+1)pb=dp[b]+cc[b]*(bt[b]-co[id]);
    dp[a]=MAX(pa,pb);
    cc[a]+=cc[b];
    bt[a]=co[id];
    f[a]=MAX(f[a],f[b]);
  }
  /*for(i=1;i<=n;i++){
    if(p[i]==0)printf("%d %d %d %d %d\n",i-1,dp[i],cc[i],bt[i],f[i-1]);
  }
  printf("\n");//*/
}
int main(){
  int k,i,t,r,q[100010],a,b,c;
  scanf("%d %d %d",&n,&m,&k);
  for(i=0;i<n;i++)ta[i]=f[i]=-1;
  for(i=0;i<n;i++)bt[i+1]=k;
  for(i=0;i<n;i++)cc[i+1]=1;
  for(i=0;i<m;i++){
    scanf("%d %d %d",&a,&b,&c);
    --a; --b;
    nt[i  ]=ta[to[i+m]=a];
    nt[i+m]=ta[to[i  ]=b];
    co[ta[a]=i]=co[ta[b]=i+m]=c;
    hin(c);
  }
  q[t=0]=f[0]=0;
  for(r=1;r-t;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){
      if(f[to[i]]+1||f[q[t]]>=co[i])continue;
      f[to[i]]=f[q[t]]+1;
      q[r++]=to[i];
    }
  }
  //for(i=0;i<n;i++)printf("%d %d\n",i,f[i]);
  for(i=0;i<m;i++)Union(hout()-1);
  //for(i=0;i<n;i++)printf("%d %d\n",i,dp[i]);
  for(i=1;p[i];i=p[i]);
  printf("%d\n",dp[i]+bt[i]*cc[i]);
  return 0;
}
