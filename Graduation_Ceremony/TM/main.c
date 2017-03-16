#include<stdio.h>
int MIN(int a,int b){return a<b?a:b;}
int MAX(int a,int b){return a<b?b:a;}
int Y[]={-1,0,1,0};
int X[]={0,1,0,-1};
int main(){
  int k,i,j,max=0,l[3010],r[3010],u[3010],d[3010],w;
  char s[3010],c[]={"URDL"};
  scanf("%s %d",s,&k);
  for(i=0;i<k+2;i++)l[i]=r[i]=u[i]=d[i]=0;
  for(i=0;s[i];i++){
    for(w=0;s[i]-c[w];w++);
    for(j=k;j;j--){
      l[j]=MIN(-r[j-1],l[j])+X[w];
      r[j]=MAX(-l[j-1],r[j])+X[w];
      u[j]=MIN(-d[j-1],u[j])+Y[w];
      d[j]=MAX(-u[j-1],d[j])+Y[w];
    }
    r[0]=l[0]+=X[w];
    u[0]=d[0]+=Y[w];
  }
  for(i=0;i<=k;i++)max=MAX(max,MAX(-l[i],r[i])+MAX(-u[k-i],d[k-i]));
  printf("%d\n",max);
  return 0;
}
      
