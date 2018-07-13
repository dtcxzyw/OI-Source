#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=100000;
bool flag[size]={};
struct Edge{
	int u,v,w;
	bool operator<(Edge rhs) const{
		return w>rhs.w;
	}
} E[size];
int fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n,k;
	n=read();
	k=read();
	for(int i=0;i<k;++i)flag[read()]=true;
	long long sum=0;
	for(int i=1;i<n;++i){
		E[i].u=read();
		E[i].v=read();
		E[i].w=read();
		sum+=E[i].w;
	}
	std::sort(E+1,E+n);
	for(int i=0;i<n;++i)fa[i]=i;
	for(int i=1;i<n;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv && !(flag[fu]&&flag[fv])){
			sum-=E[i].w;
			fa[fu]=fv;
			flag[fv]|=flag[fu];
		}
	}
	printf("%lld\n",sum);
	return 0;
}

