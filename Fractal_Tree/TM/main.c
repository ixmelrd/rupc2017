#include<stdio.h>
double r=0,d[100010],p;
int ta[100010],nt[200010],to[200010],co[200010];
void mkls(int v,int e,int *a,int *b,int *c){
  int i;
  for(i=0;i<=v;i++)ta[i]=d[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    co[ta[b[i]]=i+e]=co[ta[a[i]]=i]=c[i];
  }
}
double f(int s){//printf("%d\n",s);
  int i;
  d[s]=r;
  for(i=ta[s];i+1;i=nt[i]){
    if(d[to[i]]<0)d[s]+=(f(to[i])+co[i])*p;
  }
  return d[s];
}
int main(){
  int n,m,a[100010],b[100010],c[100010],ba[100010],bb[100010],bc[100010],i;
  scanf("%lf %d",&p,&n);//printf("%f\n",p);
  for(i=0;i<n-1;i++)scanf("%d %d %d",&a[i],&b[i],&c[i]);
  /*scanf("%d",&m);
  for(i=0;i<m-1;i++)scanf("%d %d %d",&ba[i],&bb[i],&bc[i]);
  */
  m = n;
  for(i=0;i<n-1;i++)ba[i] = a[i], bb[i] = b[i], bc[i] = c[i];
    
  
  mkls(m,m-1,ba,bb,bc);
  r=f(1);//printf("%f\n",r);
  mkls(n,n-1,a,b,c);
  printf("%.10lf\n",f(1));
  return 0;
}
