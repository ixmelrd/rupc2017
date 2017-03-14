#include<stdio.h>
int MIN(int a,int b){return a<b?a:b;}
int R=1,C=1,H[2000010],N[2000010];
//評価関数（いまはMIN）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]||(N[H[a]]==N[H[b]]&&H[a]%2<H[b]%2)?1:0;
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
int main(){
  int n,m,s,g,a[100010],b[100010],t[100010],c[100010],d[100010],ans=1e9,i;
  int f[100010],w[100010];
  scanf("%d %d %d %d",&n,&m,&s,&g);
  for(i=0;i<=n;i++)f[i]=1e9;
  for(i=0;i<=n;i++)w[i]=0;
  f[s]=0;
  for(i=0;i<m;i++){
    scanf("%d %d %d %d",&a[i],&b[i],&t[i],&c[i]);
    hin(t[i]);
    hin(t[i]+c[i]);
  }
  while(C-1){
    i=hout()-1;
    if(i%2==0){//shuppatu
      if(f[a[i/2]]<t[i/2])continue;//tuitenai
      f[b[i/2]]=MIN(f[b[i/2]],t[i/2]+c[i/2]);
      d[i/2]=w[a[i/2]]+c[i/2];
    }
    else{//toutyaku
      if(b[i/2]==g)ans=MIN(ans,t[i/2]-w[a[i/2]]);  
      if(w[b[i/2]]<d[i/2])w[b[i/2]]=d[i/2];
    }
  }
  printf("%d\n",ans);
  return 0;
}
