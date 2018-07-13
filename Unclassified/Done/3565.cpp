#include <cstdio>
#include <cstring>
const int size=5010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int maxd,dcnt[size]={},c1[size],c2[size];
int DFS(int u,int fa,int d){
	++dcnt[d];
	if(d>maxd)maxd=d;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(fa!=v)DFS(v,u,d+1);
	}
}
int main(){
	int n;
	scanf("%d",&n);
	int u,v;
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	long long ans=0;
	for(int r=1;r<=n;++r){
		memset(c1,0,sizeof(c1));
		memset(c2,0,sizeof(c2));
		for(int i=last[r];i;i=E[i].next){
			int v=E[i].to;
			maxd=0;
			DFS(v,r,1);
			for(int j=1;j<=maxd;++j){
				ans+=1LL*dcnt[j]*c2[j];
				c2[j]+=c1[j]*dcnt[j];
				c1[j]+=dcnt[j];
				dcnt[j]=0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}

