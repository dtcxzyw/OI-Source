#include <cstdio>
#include <cstring>
const int size=205;
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
} E[size*size+10];
int last[size],cnt;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
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
const char* foo(){
	int n=read();
	cnt=0;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(read())addEdge(j,i);
	memset(pair,0,sizeof(pair));
	for(int i=1;i<=n;++i){
		memset(flag,0,sizeof(flag));
		if(!match(i))return "No";
	}
	return "Yes";
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)
		puts(foo());
	return 0;
}

