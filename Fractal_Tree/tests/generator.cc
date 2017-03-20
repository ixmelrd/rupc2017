#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <sstream>
#include <map>
using namespace std;
 
#define RND(a,b) ((int)( (unsigned int)rand()%((b)-(a)+1) + (a)))


struct UnionFind {
  vector<int> data;
  UnionFind(int size) : data(size, -1) { }
  bool unionSet(int x, int y) {
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return x != y;
  }
  bool findSet(int x, int y) {
    return root(x) == root(y);
  }
  int root(int x) {
    return data[x] < 0 ? x : data[x] = root(data[x]);
  }
  int size(int x) {
    return -data[root(x)];
  }
};



struct Edge{
	int a,b,c;
	Edge(int a,int b,int c) : a(a),b(b),c(c){}
};

struct Input{
	double p;
	vector<Edge> es;
	
	bool verify(){
		int N = es.size() + 1;
		assert(2 <= N && N <= 100000);

		UnionFind uf(N);
		for( auto e: es ){
			assert(1 <= e.a and e.a <= N );
			assert(1 <= e.b and e.b <= N );
			assert(1 <= e.c and e.c <= 1000 );
			uf.unionSet(e.a-1,e.b-1);
		}
		for(int i = 0 ; i < N ; i++){
			assert( uf.root(i) == uf.root(0));
		}
		return 1;
	}
};

class Generator{
private:
	string name;
	int num;
public:
	Generator(){
		name = "";
		num = -1;
	}
	int getNum() const{ return num; }
	void set(string name_,int x){
		setName(name_);
		setNum(x);
	}
	void setName(string name_){
		name = name_;
	}
	void setNum(int x){
		num = x;
	}
	void generate(Input inp){
		inputCreate_(inp,name.c_str(),num);
		num++;
	}

	void inputCreate_(Input data,const char *special,int casenum){
		assert( data.verify() );
		FILE *inFile;
		char inm[256];
		sprintf(inm,"./%s%02d.in",special,casenum);
		inFile = fopen(inm,"w");
		
		////////
		fprintf(inFile,"%.2lf\n",data.p);
		fprintf(inFile,"%lu\n",data.es.size()+1);
		for( auto x : data.es ) 
			fprintf(inFile,"%d %d %d\n",x.a,x.b,x.c);
		fclose(inFile);
	}
};

Input random(int a,int b,double p){
	int n = RND(a,b);
	UnionFind uf(n);
	vector<Edge> es;
	for(int i = 0 ; i < n - 1 ; ){
		int a = RND(0,n-1);
		int b = RND(0,n-1);
		if( uf.root(a) != uf.root(b) ){
			uf.unionSet(a,b);
			int c = RND(1,1000);
			es.push_back({a+1,b+1,c});
			i++;
		}
	}
	return {p,es};
}


Input line(int n,double p){
	UnionFind uf(n);
	vector<Edge> es;
	for(int i = 0 ; i < n - 1 ; ){
		int a = i;
		int b = i+1;
		if( uf.root(a) != uf.root(b) ){
			uf.unionSet(a,b);
			int c = 1000;
			es.push_back({a+1,b+1,c});
			i++;
		}
	}
	return {p,es};
}
int main() {
	srand('RUPC2017-TreeTree');
	
	Generator gen;
	////// sample //////
	{
		gen.set("sample_",1);
		gen.generate({0.6,{{1,2,1}}});
		gen.generate({0.75,{{1,2,1},{1,3,3},{3,4,10}}});
		gen.generate({1.00,{{1,2,1},{1,3,3},{3,4,10}}});
		
		//gen.generate(random(8,16,10));
	}

	////// mini_rand //////
	{
		gen.set("in_",1);
		for(int i = 0 ; i < 3 ; i++){
			gen.generate(random(55,100,rand()%101/100.0));
		}
	}
	////// large_rand //////
	{
		for(int i = 0 ; i < 5 ; i++){
			gen.generate(random(99950,100000,rand()%101/100.0));
		}
		gen.generate(random(100000,100000,0.99));
		gen.generate(random(100000,100000,0.01));
		
	}
	////// other //////
	{
		gen.generate(line(100000,0.99));
		gen.generate(line(100000,0.01));
		gen.generate(line(100000,1.00));
		
	}
}