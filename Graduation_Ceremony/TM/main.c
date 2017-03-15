#include<stdio.h>
#include<stdlib.h>
int f(int a,int b){return abs(a)>abs(b)?a:b;}  
int main(){
  int k,i,j,max=0,x[3010]={};
  int y[3010]={};
  char s[3010];
  scanf("%s %d",s,&k);
  for(i=0;s[i];i++){
    if(s[i]=='R'){
      for(j=k;j;j--)x[j]=f(-x[j-1]+1,x[j]+1);
      x[0]++;
    }
    if(s[i]=='L'){
      for(j=k;j;j--)x[j]=f(-x[j-1]-1,x[j]-1);
      x[0]--;
    }
    if(s[i]=='U'){
      for(j=k;j;j--)y[j]=f(-y[j-1]+1,y[j]+1);
      y[0]++;
    }
    if(s[i]=='D'){
      for(j=k;j;j--)y[j]=f(-y[j-1]-1,y[j]-1);
      y[0]--;
    }
  }
  for(i=0;i<k;i++)x[i+1]=f(x[i+1],x[i]);
  for(i=0;i<k;i++)y[i+1]=f(y[i+1],y[i]);
  for(i=0;i<=k;i++){//printf("%d %d\n",x[i],y[i]);
    if(max<abs(x[i])+abs(y[k-i]))max=abs(x[i])+abs(y[k-i]);
  }
  printf("%d\n",max);
  return 0;
}
      
