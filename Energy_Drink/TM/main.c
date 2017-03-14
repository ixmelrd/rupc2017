#include<stdio.h>
int R=1,C=1,H[600010],N[600010],d[600010];
//評価関数（いまはMIN）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]||N[H[a]]==N[H[b]]&&d[H[a]]>d[H[b]]?1:0;
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
int lb(int l,int r,int n,int *d){
  int m=(l+r)/2;
  if(l==r)return m;
  return n<=d[m]?lb(l,m,n,d):lb(m+1,r,n,d);
}
int main(){
  int n,r=0,i,a,b,c,s[300010];
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d %d",&a,&b);
    d[R]=a;
    hin(b);
    d[R]=b;
    hin(a);
  }
  i=1;
  while(i%2)i=hout();
  s[r=0]=d[i];
  while(C-1){
    i=hout();//1->swap 0->normal
    c=s[r]<d[i]?r+1:lb(0,r,d[i],s);
    if(c%2==i%2){
      s[c]=d[i];
      if(c>r)r++;
    }
  }
  printf("%d\n",r+1);
  return 0;
}
