#include <cstdio>
#include <cstring>
struct Edge{
	int to,next;
} E[10001];
int last[101]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
bool flag[101];
int pair[101]={},sln[101]={};
bool match(int u){
	if(flag[u])return false;
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!pair[v] || match(pair[v])){
			pair[v]=u;
			sln[u]=v;
			return true;
		}
	}
	return false;
}
int read(){
	int res=0,c;
	do {
		c=getchar();
		if(c=='-')return -1;
	}while(c<'0'||c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,m;
	n=read();
	m=read();
	int u,v;
	while(true){
		u=read();
		v=read();
		if(u==-1)break;
		else addEdge(u,v);
	}
	int ans=0;
	for(int i=1;i<=m;++i){
		memset(flag,0,sizeof(flag));
		if(match(i))++ans;
	}
	if(ans){
		printf("%d\n",ans);
		for(int i=1;i<=m;++i)
			if(sln[i] && pair[sln[i]]==i)printf("%d %d\n",i,sln[i]);
	}
	else puts("No Solution!");
	return 0;
}

