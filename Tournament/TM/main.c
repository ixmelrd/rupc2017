#include<stdio.h>
int main(){
  int n,m,i;
  scanf("%d %d",&n,&m);
  for(i=0;i<m;i++)scanf("%*d");
  printf("%d\n",n-m-1);
  return 0;
}
