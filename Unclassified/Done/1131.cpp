#include <cstdio>
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
const int size=500001;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size]={};
long long ans=0;
long long DFS(int u,long long len){
	flag[u]=true;
	long long maxl=len,sum=0,ccnt=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			long long l=DFS(v,E[i].w+len);
			if(l>maxl)maxl=l;
			sum+=l,++ccnt;
		}
	}
	ans+=maxl*ccnt-sum;
	return maxl;
}
int main(){
	int n=read();
	int s=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(s,0);
	printf("%lld\n",ans);
	return 0;
}

