#include <cstdio>
#include <algorithm>
struct Mogic{
	int t,b;
} m[100000];
bool cmp(Mogic lhs,Mogic rhs){
	if(lhs.b>=0 && rhs.b>=0)
		return lhs.t<rhs.t;
	if(lhs.b<0 && rhs.b<0)
		return lhs.t+lhs.b>rhs.t+rhs.b;
	return lhs.b>rhs.b;
}
bool foo(){
	int n,T;
	scanf("%d%d",&n,&T);
	for(int i=0;i<n;++i)
		scanf("%d%d",&m[i].t,&m[i].b);
	std::sort(m,m+n,cmp);
	for(int i=0;i<n;++i)
		if(T>0 && T>m[i].t)T+=m[i].b;
		else return false;
	return T>0;
}
int main(){
	int z;
	scanf("%d",&z);
	while(z--)puts(foo()?"+1s":"-1s");
	return 0;
}

