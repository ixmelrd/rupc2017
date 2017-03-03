#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
int MIN(int a,int b){return a<b?a:b;}
void makeNstring(int n,char *name){
  FILE *f;
  int i,l,use=0;
  f=fopen(name,"w");
  fprintf(f,"%d\n",n);
  for(i=0;i<n;i++){
    l=rnd.next(1,MIN(MAX_SUM_LEN-use-(n-i-1),MAX_SUM_LEN/n*2));
    use+=l;
    while(l--)fprintf(f,"%c",rnd.next(0,25)+'a');
    fprintf(f,"\n");
  }//printf("%d\n",use);
  fclose(f);
}
void make1string(char *name){
  FILE *f;
  int i;
  f=fopen(name,"w");
  fprintf(f,"1\n");
  for(i=0;i<MAX_SUM_LEN;i++)fprintf(f,"%c",rnd.next(0,25)+'a');
  fprintf(f,"\n");
  fclose(f);
} 
void challenge00(){
  FILE *f;
  int i;
  f=fopen("60_Challenge_00.in","w");
  fprintf(f,"1\na");
  for(i=1;i<26*26*26;i++)fprintf(f,"a%c%c%c",i/26/26+'a',i/26%26+'a',i%26+'a');
  fprintf(f,"\n");
  fclose(f);
}
int main(){
  // 乱数のシードを設定
  // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
  rnd.setSeed(time(0)+getpid());//[]
  int i;
  char s[100];
  //文章数が多いのを作る
  for(i=0;i<10;i++){
    int n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"50_random_short_%02d.in",i);
    makeNstring(n,s);
  }
  //文書数が少し少ないのを作る
  for(i=0;i<10;i++){
    int n=rnd.next(MIN_N,MIN_N+500);
    sprintf(s,"51_random_long_%02d.in",i);
    makeNstring(n,s);
  }
  //1文のみを作る
  for(i=0;i<5;i++){
    sprintf(s,"52_random_MAX_%02d.in",i);
    make1string(s);
  }
  //コーナーケース
  challenge00();
  return 0;
}
