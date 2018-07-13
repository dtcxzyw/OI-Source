#include <cstdio>
const int size=101;
struct Edge{
	int to,next;
} E[size*size];
int last[size],cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int dfn[size]={},low[size],pcnt=0,st[size],ssiz=0,col[size],ccnt=0;
bool flag[size]={};
void DFS(int u){
	dfn[u]=low[u]=++pcnt;
	st[++ssiz]=u;
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!dfn[v]){
			DFS(v);
			if(low[v]<low[u])low[u]=low[v];
		}
		else if(flag[v] && dfn[v]<low[u])
			low[u]=dfn[v];
	}	
	if(dfn[u]==low[u]){
		++ccnt;	
		int v;	
		do{
			v=st[ssiz--];
			col[v]=ccnt;
			flag[v]=false;
		}
		while(u!=v);
	}
}
int in[size]={},out[size]={};
int main(){
	int n;
	scanf("%d",&n);
	int to;
	for(int i=1;i<=n;++i){
		while(true){
			scanf("%d",&to);
			if(to)addEdge(i,to);
			else break;	
		}
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			DFS(i);
	for(int i=1;i<=n;++i)
		for(int j=last[i];j;j=E[j].next){
			int v=E[j].to;
			if(col[i]!=col[v]){
				++in[col[v]];
				++out[col[i]];
			}
		}
		
	int ansA=0,ansB=0;
	for(int i=1;i<=ccnt;++i){
		ansA+=(in[i]==0);
		ansB+=(out[i]==0);
	}
	printf("%d\n",ansA);
	if(ccnt==1)puts("0");
	else printf("%d\n",ansA>ansB?ansA:ansB);
	return 0;
}

