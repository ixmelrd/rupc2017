#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

void MakeGrid(int h,int w,int n,char *name){
  FILE *f;
  int x,y,i,j;
  char s[510][510]={};
  f=fopen(name,"w");
  fprintf(f,"%d %d %d\n",h,w,n);
  for(i=0;i<h;i++){
    fprintf(f,"%d %d",rnd.next(0,w-1),rnd.next(0,h-1));
    for(j=1;j<w;j++)fprintf(f," %d %d",rnd.next(0,w-1),rnd.next(0,h-1));
    fprintf(f,"\n");
  }
  for(i=0;i<n;i++){
    do{
      x=rnd.next(0,w-1);
      y=rnd.next(0,h-1);
    }while(s[y][x]);
    s[y][x]=1;
    fprintf(f,"%d %d\n",x,y);
  }
  fclose(f);
}
void Challenge00(){
  FILE *f=fopen("60_Challenge_00.in","w");
  int i,j,k=1;
  fprintf(f,"%d %d 2\n",MAX_H,MAX_W);
  for(i=0;i<MAX_H;i++){
    for(j=1;j<MAX_W;j++)fprintf(f,"%d %d ",j,i);
    if(i==MAX_H-1)fprintf(f,"%d %d\n",MAX_W-1,MAX_H-1);
    else          fprintf(f,"0 %d\n",i+1);
  }
  fprintf(f,"0 0\n1 0\n");
  fclose(f);
}
void Challenge01(){
  FILE *f=fopen("60_Challenge_01.in","w");
  int i,j,k=1;
  fprintf(f,"%d %d %d\n",MAX_H,MAX_W,MAX_H*MAX_W);
  for(i=0;i<MAX_H;i++){
    fprintf(f,"0 %d",i);
    for(j=1;j<MAX_W;j++)fprintf(f," %d %d",j,i);
    fprintf(f,"\n");
  }
  for(i=0;i<MAX_H*MAX_W;i++)fprintf(f,"%d %d\n",i/MAX_W,i%MAX_W);
  fclose(f);
}
void Challenge02(){
  char s[100]={"60_Challenge_02.in"};
  MakeGrid(MAX_H,MAX_W,1,s);
}

      
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
    n=rnd.next(MIN_N,10);
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
  //コーナーケース
  Challenge00();
  Challenge01();
  Challenge02();
  return 0;

}
