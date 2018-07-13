#include <cstdio>
#include <cstring>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=51;
struct Edge{
	int to,next;
} E[size*size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int in[size],back[size];
bool checkL(int x){
	if(in[x])return !back[x];
	return true;
}
bool flag[size];
int pair[size];
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
	memset(pair,0,sizeof(pair));
	memset(last,0,sizeof(last));
	cnt=0;
	int n=read();
	for(int i=1;i<=n;++i)in[i]=read();
	for(int i=1;i<=n;++i){
		back[i]=read();
		if(in[i] && !back[i])addEdge(i,i);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(read() && in[j])
				addEdge(i,j);
	for(int i=1;i<=n;++i)
		if(checkL(i)){
			memset(flag,0,sizeof(flag));
			if(!match(i))return false;
		}
	return true;
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)puts(foo()?"^_^":"T_T");
	return 0;
}

