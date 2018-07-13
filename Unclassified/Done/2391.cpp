#include <cstdio>
#include <algorithm>
#include <cstring>
int fa[1000001]={},col[1000001]={};
int find(int x){
	return fa[x]?fa[x]=find(fa[x]):x;
}
void print(int x){
	if(x>=10)print(x/10);
	putchar('0'+x%10);
}
int main(){
	int n,m,p,q;
	scanf("%d%d%d%d",&n,&m,&p,&q);
	
	for(int i=m;i>=1;--i){
		int l=(1ll*i*p+q)%n+1,r=(1ll*i*q+p)%n+1;
		if(l>r)std::swap(l,r);
		l=find(l);
		while(l<=r){
			col[l]=i;
			fa[l]=l+1;
			l=find(l+1);
		}
	}
	
	for(int i=1;i<=n;++i){
		print(col[i]);
		putchar('\n');
	}
	return 0;
}

