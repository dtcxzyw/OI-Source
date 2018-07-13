#include <cstdio>
#include <cstring>
struct Edge{
	int to,next;
} E[1000000];
int last[60*60]={},cnt=0;
bool link[60*60][60*60]={};
void addEdge(int u,int v){
	if(!link[u][v]){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
		link[u][v]=true;
	}
}
int col[60][60][2],pair[60*60]={};
bool flag[60*60];
bool match(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			flag[v]=true;
			if(!pair[v] || match(pair[v])){
				pair[v]=u;
				return true;
			}
		}
	}
	return false;
}
char buf[60][60];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",buf[i]+1);
	int xcnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(buf[i][j]=='#')++xcnt;
			col[i][j][0]=xcnt;
		}
		++xcnt;
	}
	int ycnt=0;
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			if(buf[j][i]=='#')++ycnt;
			col[j][i][1]=ycnt;
		}
		++ycnt;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(buf[i][j]=='*')
				addEdge(col[i][j][0],col[i][j][1]);
	int res=0;
	for(int i=0;i<=xcnt;++i){
		memset(flag,0,sizeof(flag));
		if(match(i))++res;
	}
	printf("%d\n",res);
	return 0;
}

