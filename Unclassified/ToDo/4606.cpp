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
const int size=100005;
struct Edge{
	int to,next;
} E[size*4];
int last[size],cnt;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
void foo(){
	memset(last,0,sizeof(last));
	cnt=0;
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	
	int q=read();
	for(int i=0;i<q;++i){
		int k=read();
		for(int j=0;j<k;++j)
			
	}
}
int main(){
	int t=read();
	while(t--)foo();
	return 0;
}

