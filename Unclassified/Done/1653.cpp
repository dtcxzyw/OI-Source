#include <cstdio>
#include <cstring>
#include <algorithm>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=(c=='-');
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?0:res;
}
const int size=200010,inf=0x3f3f3f3f;
int fa[size],ans[size];
int find(int x){
	if(x!=fa[x]){
		int nf=find(fa[x]);
		ans[x]=std::min(ans[x],ans[fa[x]]);
		return fa[x]=nf;
	}
	return x;
}
void merge(int u,int v,int t){
	u=find(u),v=find(v);
	if(u!=v){
		if(u==1)fa[v]=u,ans[v]=t;
		else fa[u]=v,ans[u]=t;
	}
}
int l[size],r[size],x[size*2],y[size*2];
bool flag[size][2]={};
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		fa[i]=i;
		l[i]=read();
		r[i]=read();
		if(!l[i])flag[i][0]=true;
		if(!r[i])flag[i][1]=true;
	}
	for(int i=0;i<m;++i){
		x[i]=read();
		int s=read();
		if(s==1)y[i]=l[x[i]];
		else y[i]=r[x[i]];
		flag[x[i]][s-1]=true;
	}
	for(int i=1;i<=n;++i){
		if(!flag[i][0])merge(i,l[i],m);
		if(!flag[i][1])merge(i,r[i],m);
	}
	memset(ans,0x3f,sizeof(ans));
	for(int i=m-1;i>=0;--i)
		if(y[i])
			merge(x[i],y[i],i);
	for(int i=1;i<=n;++i){
		find(i);
		if(ans[i]==inf)puts("-1");
		else printf("%d\n",ans[i]);
	}
	return 0;
}

