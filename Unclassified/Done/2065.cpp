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
const int size=501;
int L[size],R[size];
struct Edge{
	int to,next;
} E[size*size];
int last[size],cnt;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int pair[size];
bool flag[size];
bool match(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			flag[v]=true;
			if(!pair[v]||match(pair[v])){
				pair[v]=u;
				return true;
			}
		}
	}
	return false;
}
void foo(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)L[i]=read();
	for(int i=1;i<=m;++i)R[i]=read();
	cnt=0;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(gcd(L[i],R[j])>1)
				addEdge(i,j);
	memset(pair,0,sizeof(pair));
	int ans=0;
	for(int i=1;i<=n;++i){
		memset(flag,0,sizeof(flag));
		if(match(i))++ans;
	}
	printf("%d\n",ans);
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)foo();
	return 0;
}

