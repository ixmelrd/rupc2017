signed main(void){
  int n,m,i,a[1123],b,c,sum=0,judge=0;
  scanf("%d %d",&n,&m);
  for(i=0;i<n;i++)scanf("%d",&a[i]);
  do{
      b=-(c=0x7fffffff);
      for(i=0;i<m;i++){
	b=(b>a[(judge+i)%n])?b:a[(judge+i)%n];
	c=(c<a[(judge+i)%n])?c:a[(judge+i)%n];
	}
      sum+=b;
      judge+=i;
    }while(judge%n);
  printf("%d\n",sum);
}

