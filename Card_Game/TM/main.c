#include<stdio.h>
long long R=1,C=1,H[2000010],N[2000010],s=0,d[20][100110],min;
//評価関数（いまはMIN）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]?1:0;
}
//挿入関数
void hin(long long a){
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
long long CO[100110];
void dijk(int v,int e,int *fr,int *to,int *co,int mi){
  int i,id[100110],ta[100110],nt[300110],f[100110]={0};
  for(i=0;i<=v;i++)ta[i]=-1;
  for(i=0;i<=v;i++)CO[i]=1e18;
  for(i=CO[mi]=0;i<e;i++){
    nt[i]=ta[fr[i]];
    ta[fr[i]]=i;
  }
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[mi];i+1;i=nt[i]){
      if(CO[to[i]]>CO[mi]+co[i])hin(CO[id[R]=to[i]]=CO[mi]+co[i]);
    }
    while(f[mi]&&C-1)mi=id[hout()];
  }
}
int  a[300110],b[300110],c[300110];
int main(){
  int n,m,r,q,x,y,z,i,j;
  scanf("%d %d %d %d",&n,&m,&r,&q);
  for(i=0;i<m;i++)scanf("%d %d %d",&b[i],&a[i],&c[i]);
  for(i=0;i<n;i++){
    a[i+m]=(i+1)%r+n+1;
    b[i+m]=i+1;
    c[i+m]=0;
  }
  for(i=0;i<r;i++){
    R=C=1;
    dijk(n+r,m+n,a,b,c,i+n+1);
    for(j=1;j<=n;j++)d[i][j]=CO[j];
  }
  for(i=0;i<q;i++){
    scanf("%d %d %d",&x,&y,&z);
    min=1e18;
    for(j=0;j<r;j++){
      if(min>d[j][x]+d[j][y])min=d[j][x]+d[j][y];
    }
    if(min<z)s+=z-min;
    //s+=z-min;
  }
  printf("%lld\n",s);
  return 0;
}
  
    
