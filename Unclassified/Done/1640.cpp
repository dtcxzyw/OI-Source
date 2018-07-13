#include <cstdio>
#include <cstring>
const int size=1000001;
struct Edge{
	int to,next;
} E[size*2];
int last[10001]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int pair[size]={};
bool flag[size]={};
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
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		addEdge(read(),i);
		addEdge(read(),i);
	}
	int ans=0;
	for(int i=1;i<=10000;++i){
		memset(flag,0,n+1);
		if(match(i))ans=i;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}

