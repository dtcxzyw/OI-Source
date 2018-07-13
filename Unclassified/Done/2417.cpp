#include <cstdio>
#include <cstring>
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
struct Edge{
	int to,next;
} E[2000001];
int last[20001],cnt;
bool linked[20001][101];
void addEdge(int u,int v){
	if(linked[u][v])return;
	linked[u][v]=true;
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
bool flag[20001];
int pair[101];
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
bool foo(){
	int p=read();
	int n=read();
	memset(last,0,sizeof(last));
	memset(linked,0,sizeof(linked));
	cnt=0;
	for(int i=1;i<=p;++i){
		int m=read();
		for(int j=0;j<m;++j)
			addEdge(p,read());
	}
	if(n<p)return false;
	memset(pair,0,sizeof(pair));
	for(int i=1;i<=p;++i){
		memset(flag,0,sizeof(flag));
		if(!match(p))
			return false;
	}
	return true;
}
int main(){
	int t=read();
	while(t--)puts(foo()?"YES":"NO");
	return 0;
}

