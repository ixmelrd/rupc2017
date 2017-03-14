#include<stdio.h>
#include "testlib.h"
#include "constraints.hpp"
#include <unistd.h>
int a[200010],b[200010],t[200010],c[200010],r[200010];
int MIN(int a,int b){return a<b?a:b;}
//p本以下でsからgのパスを作る
void makeP(int p,int n,int s,int g){//printf("PP\n");
  int x=MAX_t/p,y=MAX_c/p,bt=0,i;
  for(i=0;i<p;i++){
    a[i]=i?b[i-1]:s;
    b[i]=(a[i]-1+rnd.next(1,n-1))%n+1;
    if(i)bt=t[i-1]+c[i-1];
    t[i]=rnd.next(bt,MIN(bt+x,MAX_t));
    c[i]=rnd.next(MIN_c,MIN(y,MAX_t-t[i]));
  }
  if(a[p-1]-g)b[p-1]=g;
}
void makeG(int n,int m,int s,int g,char *name){
  FILE *f;
  int i,p;
  f=fopen(name,"w");//printf("F %d %d\n",n,m);
  fprintf(f,"%d %d %d %d\n",n,m,s,g);
  p=rnd.next(1,MIN(n,m));
  makeP(p,n,s,g);//printf("P\n");
  for(i=0;i<m;i++)r[i]=i;
  for(i=p;i<m;i++){
    a[i]=rnd.next(MIN_N,n);
    b[i]=(a[i]-1+rnd.next(1,n-1))%n+1;
    t[i]=rnd.next(MIN_t,MAX_t);
    c[i]=rnd.next(MIN_c,MAX_c);
  }
  shuffle(r,r+m);
  for(i=0;i<m;i++)fprintf(f,"%d %d %d %d\n",a[r[i]],b[r[i]],t[r[i]],c[r[i]]);
  fclose(f);//printf("G\n");
}
int main(){
  int i,n,m,s,g;
  char c[100];
  // 乱数のシードを設定
  // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになるのを防ぐ
  rnd.setSeed(time(0)+getpid());

  for(i=0;i<5;i++){
    n=rnd.next(MIN_N,10);
    m=rnd.next(MIN_M,10);
    s=g=rnd.next(1,n);
    //while(s==g)g=rnd.next(MIN_N,n);
    g=rnd.next(1,n);
    sprintf(c,"50_random_small_%02d.in",i);
    makeG(n,m,s,g,c);
  }
  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    m=rnd.next(MIN_M,MAX_M);
    s=g=rnd.next(1,n);
    //while(s==g)g=rnd.next(MIN_N,n);
    g=rnd.next(1,n);
    sprintf(c,"51_random_large_%02d.in",i);
    makeG(n,m,s,g,c);
  }
  for(i=0;i<5;i++){
    n=MAX_N;
    m=MAX_M;
    s=g=rnd.next(1,n);
    //while(s==g)g=rnd.next(MIN_N,n);
    g=rnd.next(1,n);
    sprintf(c,"52_random_MAX_%02d.in",i);
    makeG(n,m,s,g,c);
  }
}
