#include<stdio.h>
int n;
int f(int *d,int *p){
  int i,a[300010]={};
  for(i=0;i<n;i++){
    if(a[d[p[i]]])return 1;
    a[d[p[i]]]=1;
  }
  return 0;
}
int h,w,p[300010],d[50][300010],i,j,s=0,x,y;
int main(){
  scanf("%d %d %d",&h,&w,&n);
  for(i=0;i<h*w;i++){
    scanf("%d %d",&x,&y);
    d[0][i]=x*w+y;
  }
  for(i=0;i<n;i++){
    scanf("%d %d",&x,&y);
    p[i]=x*w+y;
  }
  for(i=0;(1<<i)<=h*w;i++){
    for(j=0;j<h*w;j++)d[i+1][j]=d[i][d[i][j]];
  }
  i++;
  while(i--){
    if(f(d[i],p)==0){
      s+=1<<i;
      for(j=0;j<n;j++)p[j]=d[i][p[j]];
    }
  }
  printf("%d\n",s<h*w?s+1:-1);
  return 0;
}
