#include <cstdio>
#include <algorithm>
struct Edge{
	int to,next;
} E[50*50*4];
int last[50*50]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int pair[50*50]={},vis[50*50]={},timeStamp=0;
bool flag[50*50]={};
bool match(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(flag[v])continue;
		if(vis[v]==timeStamp)continue;
		vis[v]=timeStamp;
		if(!pair[v] || match(pair[v])){
			pair[v]=u,pair[u]=v;
			return true;
		}
	}
	return false;
}
int iabs(int x){
	return x>=0?x:-x;
}
int dis(int x1,int y1,int x2,int y2){
	int dx=iabs(x1-x2),dy=iabs(y1-y2);
	return dx+dy;
}
int id[50][50]={};
char buf[50][50];
bool state[2010];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int sx,sy;
	for(int i=1;i<=n;++i){
		scanf("%s",buf[i]+1);
		for(int j=1;j<=m;++j)
			if(buf[i][j]=='.')
				sx=i,sy=j,buf[i][j]='X';	
	}
	int icnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if((buf[i][j]=='O' && (dis(i,j,sx,sy)&1))||(buf[i][j]=='X'&& !(dis(i,j,sx,sy)&1)))
				id[i][j]=++icnt;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(id[i][j]){
				if(id[i][j+1])addEdge(id[i][j],id[i][j+1]);
				if(id[i][j-1])addEdge(id[i][j],id[i][j-1]);
				if(id[i+1][j])addEdge(id[i][j],id[i+1][j]);
				if(id[i-1][j])addEdge(id[i][j],id[i-1][j]);
			}
	for(int i=1;i<=icnt;++i){
		if(!pair[i]){
			++timeStamp;
			match(i);
		}
	}
	int k;
	scanf("%d",&k);
	k*=2;
	for(int i=1;i<=k;++i){
		int u=id[sx][sy];
		if(pair[u]){
			int v=pair[u];
			pair[u]=pair[v]=0;
			flag[u]=true;
			++timeStamp;
			state[i]=!match(v);
		}
		else{
			flag[u]=true;
			state[i]=false;
		}
		scanf("%d%d",&sx,&sy);
	}
	int res=0;
	for(int i=1;i<=k;i+=2)
		if(state[i] && state[i+1])
			++res;
	printf("%d\n",res);
	for(int i=1;i<=k;i+=2)
		if(state[i] && state[i+1])
			printf("%d\n",(i+1)/2);
	return 0;
}

