#include <cstdio>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=50005;
struct Edge{
	int to,next;
	long long w;
} E[200050];
int last[size]={},cnt=0;
void addEdge(int u,int v,long long w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
struct Base{
	long long bit[60];
	void insert(long long x){
		for(int i=59;i>=0;--i)
			if(x&(1LL<<i)){
				if(bit[i])x^=bit[i];
				else{
					bit[i]=x;
					break;
				}
			}
	}
	long long count(long long res) const{
		for(int i=59;i>=0;--i)
			if((res^bit[i])>res)
				res^=bit[i];
		return res;
	}
} ans;
bool flag[size]={};
long long d[size]={};
void DFS(int u){
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(flag[v])ans.insert(d[u]^d[v]^E[i].w);
		else{
			d[v]=d[u]^E[i].w;
			DFS(v);
		}
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		long long w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1);
	printf("%lld\n",ans.count(d[n]));
	return 0;
}

