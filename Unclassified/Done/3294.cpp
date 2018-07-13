#include <cstdio>
#include <algorithm>
const int bsiz=520000,size=101000;
char buf[bsiz];
int read(){
	int cnt=0,c;
	do c=getchar();
	while(c<'a'||c>'z'); 
	while('a'<=c&&c<='z'){
		buf[++cnt]=c;
		c=getchar();
	}
	return cnt;
}
int son[bsiz][26]={},id[bsiz]={},ccnt=0;
void insert(int cur){
	int siz=read();
	int p=0,cp=0;
	for(int i=siz;i;--i){
		int x=buf[i]-'a';
		if(!son[p][x])son[p][x]=++ccnt;
		p=son[p][x];
	}
	id[p]=cur;
}
struct Edge{
	int to,next;
} E[size];
int fa[size],siz[size],last[size]={},ecnt=0;
void addEdge(int u,int v){
	++ecnt;
	E[ecnt].to=v,E[ecnt].next=last[u];
	last[u]=ecnt;
	fa[v]=u;
}
void calcFa(int u,int cp){
	int x=id[u];
	if(x){
		addEdge(cp,x);
		cp=x;
		siz[x]=1;
	}
	for(int i=0;i<26;++i)
		if(son[u][i])
			calcFa(son[u][i],cp);
	if(x)siz[fa[x]]+=siz[x];
}
int order[size],tmp[size],cnt=0;
bool cmp(int u,int v){
	return siz[u]<siz[v];
}
int end=0;
void slove(int u){
	order[u]=cnt++;
	int begin=end;
	for(int i=last[u];i;i=E[i].next)tmp[end++]=E[i].to;
	std::sort(tmp+begin,tmp+end,cmp);
	int cend=end;
	for(int i=begin;i<cend;++i)
		slove(tmp[i]);
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)insert(i);
	calcFa(0,0);
	slove(0);
	long long res=0;
	for(int i=1;i<=n;++i)res+=order[i]-order[fa[i]];
	printf("%lld\n",res);
	return 0;
}

