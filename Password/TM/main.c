#include<stdio.h>
char s[200010],w[5];
int main(){
  int n,i,j,k,l,a,b=1,c=0;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%s",s+c);
    while(s[c++]);
  }
  for(i=0;i<4;i++){
    int d[500010]={};
    for(k=0;k<c;k++){
      for(l=a=0;l<=i;l++){
	if(s[k+l]==0)break;
	a=a*26+s[k+l]-'a';
      }
      if(l>i)d[a]=1;
    }
    b*=26;
    for(j=0;j<b;j++){
      if(d[j]==0){
	w[i+1]=0;
	for(k=j;i+1;k/=26)w[i--]=k%26+'a';
	printf("%s\n",w);
	return 0;
      }
    }
  }
}
      
