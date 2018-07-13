#include <cstdio>
const int size=3010,L=size-1,R=size-2,T=size-3,B=size-4;
long long x[size],y[size];
double dis(int a,int b){
	double dx=x[a]-x[b],dy=y[a]-y[b];
	return dx*dx+dy*dy;
}
int fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int a,int b){
	a=find(a),b=find(b);
	if(a!=b)fa[a]=b;
}
bool check(){
	int fl=find(L),fr=find(R),ft=find(T),fb=find(B);
	return fl==fr || ft==fb || fl==ft || fr==fb;
}
bool check(double r,int n,long long w,long long h){
	for(int i=1;i<=n;++i)fa[i]=i;
	fa[L]=L,fa[R]=R,fa[T]=T,fa[B]=B;
	for(int i=1;i<=n;++i){
		if(x[i]-1<r)merge(L,i);
		if(y[i]-1<r)merge(T,i);
		if(w-x[i]<r)merge(R,i);
		if(h-y[i]<r)merge(B,i);
		if(check())return false;
	}
	double r2=4.0*r*r;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j)
			if(dis(i,j)<r2){
				merge(i,j);
				if(check())return false;
			}
	}
	return true;
}
int main(){
	int n;
	long long w,h;
	scanf("%d%lld%lld",&n,&w,&h);
	for(int i=1;i<=n;++i)scanf("%lld%lld",&x[i],&y[i]);
	double l=0.0,r=w<h?w:h;
	while(r-l>=0.001){
		double mid=(l+r)/2.0;
		if(check(mid,n,w,h))l=mid;
		else r=mid;
	}
	printf("%.2lf\n",l);
	return 0;
}

