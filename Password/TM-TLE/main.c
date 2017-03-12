#include<stdio.h>
#include<string.h>
char s[600010],w[5];
int main(){
  int n,i,j,k,l,a,b=1,c=0;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%s",s+c);
    while(s[c++]);
    s[c-1]='_';
  }
  s[c-1]=0;
  for(i=0;i<4;i++){
    b*=26;
    for(j=0;j<b;j++){
      c=j;
      for(k=0;k<=i;k++){
	w[i-k]=c%26+'a';
	c/=26;
      }
      if(strstr(s,w)==NULL){
	printf("%s\n",w);
	return 0;
      }
    }
  }
}
      
