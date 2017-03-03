#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>

void makeNstring(int n,char *name){
  FILE *f;
  int i,l,use=0;
  f=fopen(name,"w");
  fprintf(f,"%d\n",n);
  for(i=0;i<n;i++){
    l=rnd.next(1,MAX_SUM_LEN-use-(n-i-1));
    use+=l;
    while(l--)fprintf(f,"%c",rnd.next(0,25)+'a');
    fprintf(f,"\n");
  }//printf("%d\n",use);
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
// aとbをファイルストリームに出力する
// ファイル名は prefix_num.in (ex: 00_sample_00.in)


int main(){
    // 乱数のシードを設定
    // pidを足すことで、1秒以上間を置かずに起動したときに同じシードになってしまうのを防ぐ
  rnd.setSeed(time(0)+getpid());//[]
  int i;
  char s[100];
  for(i=0;i<10;i++){
    int n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"50_random_%02d.in",i);
    makeNstring(n,s);
  }
  challenge00();
  return 0;
}
