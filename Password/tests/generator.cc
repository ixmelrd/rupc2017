#include<stdio.h>
#include <iostream>
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
  f=fopen("60_challenge_00.in","w");
  fprintf(f,"1\na");
  for(i=1;i<26*26*26;i++)fprintf(f,"a%c%c%c",i/26/26+'a',i/26%26+'a',i%26+'a');
  fprintf(f,"\n");
  fclose(f);
}

namespace tubo28 {
    using namespace std;

    void output(const vector<string> &s, const string &name) {
        ofstream ofs(name);
        ofs << s.size() << endl;
        for (auto &e : s) {
            ofs << e << '\n';
        }
        ofs.close();
    }

    bool checkadd(string &s, const string &add) {
        if (s.size() + add.size() > 399999) return false;
        if (s.find(add) == string::npos) s += add;
        return true;
    }

    void challenge01() {
        string s;
        string w(4, ' ');
        for (char c = 'a'; c <= 'z'; ++c) {
            w[0] = c;
            for (char d = 'a'; d <= 'z'; ++d) {
                w[1] = d;
                for (char e = 'a'; e <= 'z'; ++e) {
                    w[2] = e;
                    for (char f = 'a'; f <= 'z'; ++f) {
                        w[3] = f;
                        if (!checkadd(s, w)) goto END;
                    }
                }
            }
        }

    END:
        // cout << w << endl;
        // cout << s.size() << endl;
        output({s}, "60_challenge_01.in");
    }
}
//

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

  // 時間がかかるので結果だけ置いておく
  // tubo28::challenge01();

  return 0;
}
