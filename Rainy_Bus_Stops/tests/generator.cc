#include<stdio.h>
#include "testlib.h"
#include "constraints.hpp"
#include <unistd.h>
#include <string>
#include <vector>
#include <tuple>

namespace tubo28 {
    using namespace std;
    using edge = tuple<int,int,int,int>;

    void output(int n, int s, int g, const vector<edge> &es, const string &name) {
        ofstream ofs(name);
        int m = es.size();
        ofs << n << ' ' << m << ' ' << s << ' ' << g << endl;
        for (auto &e : es) {
            int u, v, t, c;
            tie(u, v, t, c) = e;
            ofs << u << ' ' << v << ' ' << t << ' ' << c << '\n';
        }
    }

    void dence(int n, const string &name) {
        int s = 1;
        int g = n;
        vector<edge> es;
        int mid = rnd.next(1, n);
        es.emplace_back(s, mid, 50000, 1);
        es.emplace_back(mid, g, 100000, 1);
        while(es.size() < MAX_M) {
            int u = 0, v = 0;
            while(true) {
                u = rnd.next(1, n);
                v = rnd.next(1, n);
                if (n >= 4 && u == s && v == g) continue;
                if (u != v) break;
            }
            int t = rnd.next(MIN_t, MAX_t);
            int c = rnd.next(MIN_c, MAX_c);
            es.emplace_back(u, v, t, c);
        }

        output(n, 1, n, es, name);
    }
}

int a[200010],b[200010],t[200010],c[200010],r[200010];
int MIN(int a,int b){return a<b?a:b;}
//p本以下でsからgのパスを作る
void makeP(int p,int n,int s,int g){//printf("PP\n");
  int x=MAX_t/p,y=MAX_c/p,bt=0,i;
  for(i=0;i<p;i++){
    a[i]=i?b[i-1]:s;
    b[i]=(a[i]-1+rnd.next(1,n-1))%n+1;
    if(i)bt=t[i-1]+c[i-1];
    t[i]=rnd.next(bt,MIN(bt+x,MAX_t-(p-i)));
    c[i]=rnd.next(MIN_c,MIN(y,MAX_t-t[i]-(p-i)+1));
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
    n=rnd.next(MIN_N,5);
    m=rnd.next(MIN_M,5);
    s=g=rnd.next(1,n);
    while(s==g)g=rnd.next(1,n);
    //g=rnd.next(1,n);
    sprintf(c,"50_random_small_%02d.in",i);
    makeG(n,m,s,g,c);
  }
  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    m=rnd.next(MIN_M,MAX_M);
    s=g=rnd.next(1,n);
    while(s==g)g=rnd.next(1,n);
    //g=rnd.next(1,n);
    sprintf(c,"51_random_large_%02d.in",i);
    makeG(n,m,s,g,c);
  }
  for(i=0;i<5;i++){
    n=MAX_N;
    m=MAX_M;
    s=g=rnd.next(1,n);
    while(s==g)g=rnd.next(1,n);
    //g=rnd.next(1,n);
    sprintf(c,"52_random_MAX_%02d.in",i);
    makeG(n,m,s,g,c);
  }
  
  tubo28::dence(2, "60_manyedge_N2.in");
  tubo28::dence(3, "60_manyedge_N3.in");
  tubo28::dence(10, "60_manyedge_N10.in");
  tubo28::dence(100, "60_manyedge_N100.in");
  tubo28::dence(300, "60_manyedge_N300.in");
}
