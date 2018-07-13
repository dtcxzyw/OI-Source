#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=3001;
struct Edge{
	int next,to;
} E[10001];
int last[size]={},w[size],order[size],cnt=0,fa[size]={},flag[size]={};
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
void DFS(int u,int p){
	fa[u]=p;
	for(int i=last[u];i;i=E[i].next)
		if(fa[E[i].to]!=p)
			DFS(E[i].to,p);
}
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
bool cmp(int a,int b){
	return w[a]<w[b];
}
int main(){
	int n,p;
	n=read();
	p=read();
	int id;
	for(int i=0;i<p;++i){
		id=read();
		w[id]=read();
		order[i]=id;
	}
	std::sort(order,order+p,cmp);
	int r=read(),u,v;
	for(int i=0;i<r;++i){
		u=read();
		v=read();
		addEdge(u,v);
	}
	
	for(int i=0;i<p;++i){
		id=order[i];
		if(!fa[id])
			DFS(id,id);
	}
	
	for(int i=1;i<=n;++i)
        if(fa[i])flag[fa[i]]=true;
		else{
			printf("NO\n%d\n",i);
			return 0;
        }
    
    int ans=0;
	
    for(int i=1;i<=n;++i)
    	if(flag[i])ans+=w[i];

	printf("YES\n%d\n",ans);	
	return 0;
}

