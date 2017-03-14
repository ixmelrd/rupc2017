#include<stdio.h>
#include "testlib.h"
#include "constraints.hpp"
#include <unistd.h>
void makeNstring(int n,int k,char *name){
  FILE *f;
  char c[]={"URDL"};
  f=fopen(name,"w");
  while(n--)fprintf(f,"%c",c[rnd.next(0,3)]);
  fprintf(f,"\n%d\n",k);
  fclose(f);
}
void challenge00(){
  FILE *f;
  int n=MAX_S;
  char c[]={"UR"};
  f=fopen("60_challenge_00.in","w");
  while(n--)fprintf(f,"%c",c[rnd.next(0,1)]);
  fprintf(f,"\n%d\n",rnd.next(MIN_K,MAX_K-1));
  fclose(f);
}  
int main(){
  int i,n,k;
  char s[100];
  // 乱数のシードを設定
  // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになるのを防ぐ
  rnd.setSeed(time(0)+getpid());

  for(i=0;i<5;i++){
    n=rnd.next(MIN_S,10);
    k=rnd.next(MIN_K,10);
    sprintf(s,"50_random_small_%02d.in",i);
    makeNstring(n,k,s);
  }
  for(i=0;i<10;i++){
    n=rnd.next(MIN_S,MAX_S);
    k=rnd.next(MIN_K,MAX_K);
    sprintf(s,"51_random_large_%02d.in",i);
    makeNstring(n,k,s);
  }
  for(i=0;i<5;i++){
    n=MAX_S;
    k=rnd.next(MIN_K,MAX_K);
    sprintf(s,"52_random_MAX_S_%02d.in",i);
    makeNstring(n,k,s);
  }
  for(i=0;i<3;i++){
    n=MAX_S;
    k=MAX_K;
    sprintf(s,"53_random_MAX_S_K_%02d.in",i);
    makeNstring(n,k,s);
  }
  challenge00();
  return 0;
}
