#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

void MakeGrid(int h,int w,int n,char *name){
  FILE *f;
  int x,y,i,j,d[300010]={};
  char s[510][510]={};
  f=fopen(name,"w");
  fprintf(f,"%d %d %d\n",h,w,n);
  for(i=0;i<h;i++){
    fprintf(f,"%d %d",rnd.next(0,h-1),rnd.next(0,w-1));
    for(j=1;j<w;j++)fprintf(f," %d %d",rnd.next(0,h-1),rnd.next(0,w-1));
    fprintf(f,"\n");
  }
  for(i=0;i<h*w;i++)d[i]=i;
  shuffle(d,d+h*w);
  for(i=0;i<n;i++)fprintf(f,"%d %d\n",d[i]/w,d[i]%w);
  fclose(f);
}
void Challenge00(){
  FILE *f=fopen("60_Challenge_00.in","w");
  int i,j,k=1;
  fprintf(f,"%d %d 2\n",MAX_H,MAX_W);
  for(i=0;i<MAX_H;i++){
    for(j=1;j<MAX_W;j++)fprintf(f,"%d %d ",i,j);
    if(i==MAX_H-1)fprintf(f,"%d %d\n",MAX_H-1,MAX_W-1);
    else          fprintf(f,"%d 0\n",i+1);
  }
  fprintf(f,"0 0\n0 1\n");
  fclose(f);
}
void Challenge01(){
  FILE *f=fopen("60_Challenge_01.in","w");
  int i,j,k=1;
  fprintf(f,"%d %d %d\n",MAX_H,MAX_W,MAX_H*MAX_W);
  for(i=0;i<MAX_H;i++){
    fprintf(f,"%d 0",i);
    for(j=1;j<MAX_W;j++)fprintf(f," %d %d",i,j);
    fprintf(f,"\n");
  }
  for(i=0;i<MAX_H*MAX_W;i++)fprintf(f,"%d %d\n",i/MAX_W,i%MAX_W);
  fclose(f);
}
void Challenge02(){
  char s[100]={"60_Challenge_02.in"};
  MakeGrid(MAX_H,MAX_W,1,s);
}
void Challenge03(){
  FILE *f=fopen("60_Challenge_03.in","w");
  int i,j;
  fprintf(f,"%d %d %d\n",MAX_H,MAX_W,MAX_H*MAX_W);
  for(i=0;i<MAX_H;i++){
    for(j=0;j<MAX_W;j++){
      if(j)fprintf(f," ");
      fprintf(f,"%d %d",i,j%2?j-1:j+1);
    }
    fprintf(f,"\n");
  }
  for(i=0;i<MAX_H*MAX_W;i++)fprintf(f,"%d %d\n",i/MAX_W,i%MAX_W);
  fclose(f);
}
int MIN(int a,int b){return a<b?a:b;}
      
int main(){
  int i,h,w,n;
  char s[100];
  // 乱数のシードを設定
  // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになるのを防ぐ
  rnd.setSeed(time(0)+getpid());

  // 乱数ケースを10個生成
  for(i=0;i<5;i++){
    h=rnd.next(MIN_H,10);
    w=rnd.next(MIN_W,10);
    n=rnd.next(MIN_N,MIN(h*w,10));
    sprintf(s,"50_random_small_%02d.in",i);
    MakeGrid(h,w,n,s);
  }
  for(i=0;i<5;i++){
    h=rnd.next(MIN_H,MAX_H);
    w=rnd.next(MIN_W,MAX_W);
    n=rnd.next(MIN_N,h*w);
    sprintf(s,"51_random_large_%02d.in",i);
    MakeGrid(h,w,n,s);
  }
  //最大ケース
  for(i=0;i<5;i++){
    h=MAX_H;
    w=MAX_W;
    n=h*w;
    sprintf(s,"52_random_MAX_%02d.in",i);
    MakeGrid(h,w,n,s);
  }
  for(i=0;i<10;i++){
    h=rnd.next(2,MAX_H);
    w=rnd.next(2,MAX_W);
    n=rnd.next(MIN(20,h*w),MIN(60,h*w));
    sprintf(s,"53_random_N_small_%02d.in",i);
    MakeGrid(h,w,n,s);
  }
  //コーナーケース
  Challenge00();
  Challenge01();
  Challenge02();
  Challenge03();
  return 0;
}
