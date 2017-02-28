#include<iostream>
#include<string>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
using namespace std;
int exist[900*900];
string s;
void f(int a){
	if((int)s.size()-a+1<0)return;
	rep(i,(int)s.size()-a+1){
		int t=0;
		rep(j,a){
			t*=26;
			t+=s[i+j]-'a'+1;
		}
		exist[t]=true;
	}
}
int main(){
	int n;
	cin>>n;
	rep(i,n){
		cin>>s;
		rep(j,4)f(j+1);
	}
	loop(i,1,26*26*26*26+1)if(!exist[i]){
		int t=i;
		string out="";
		while(t){
			out=(char)('a'+(t-1)%26)+out;
			t=(t-1)/26;
		}
		cout<<out<<endl;
		return 0;
	}
}



