#include<stdio.h>
int main(){
  int h,w,p[30010],d[30010],i,j,n,x,y;
  scanf("%d %d %d",&h,&w,&n);
  for(i=0;i<h*w;i++){
    scanf("%d %d",&x,&y);
    d[i]=x*w+y;
  }
  for(i=0;i<n;i++){
    scanf("%d %d",&x,&y);
    p[i]=x*w+y;
  }
  for(i=0;i<h*w+10;i++){
    int f[30010]={};
    for(j=0;j<n;j++){
      p[j]=d[p[j]];
      if(f[p[j]])goto END;
      f[p[j]]=1;
    }
  }
 END:;
  printf("%d\n",i-h*w-10?i+1:-1);
  return 0;
}
