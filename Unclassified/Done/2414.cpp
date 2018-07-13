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
const int size=100100;
struct Node{
	int fail,to[26];
} T[size];
int root,fa[size],end[size],ncnt=0;
char buf[size];
void build(){
	int p=root,cnt=0;
	for(int i=0;buf[i];++i)
		switch(buf[i]){
			case 'P':end[++cnt]=p;break;
			case 'B':p=fa[p];break;
			default:{
				int c=buf[i]-'a';
				if(!T[p].to[c]){
					T[p].to[c]=++ncnt;
					fa[ncnt]=p;
				}
				p=T[p].to[c];
			}break;
		}
}
int q[size];
void cook(){
	T[root].fail=0;
	int b=0,e=1;
	q[b]=root;
	while(b!=e){
		int u=q[b++];
		for(int i=0;i<26;++i){
			int v=T[u].to[i];
			if(v){
				int p=T[u].fail;
				while(!T[p].to[i])p=T[p].fail;
				T[v].fail=T[p].to[i];
				q[e++]=v;
			}
		}
	}
}
int A[2*size]={},timeStamp=0;
void add(int x,int v){
	while(x<=timeStamp){
		A[x]+=v;
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=A[x];
		x-=x&-x;
	}
	return res;
}
struct G{
	struct Edge{
		int to,next;
	} E[size];
	int last[size],cnt;
	G():cnt(0){
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
} Q,FT;
int L[size],R[size];
void DFS(int u){
	L[u]=++timeStamp;
	for(int i=FT.last[u];i;i=FT.E[i].next)
		DFS(FT.E[i].to);
	R[u]=++timeStamp;
}
int ans[size];
void calc(){
	int p=root,cnt=0;
	add(L[root],1);
	for(int i=0;buf[i];++i)
		switch(buf[i]){
			case 'P':{
				++cnt;
				for(int i=Q.last[cnt];i;i=Q.E[i].next){
					int v=Q.E[i].to;
					int id=end[v];
					ans[i]=query(R[id])-query(L[id]-1);
				}
			}break;
			case 'B':{
				add(L[p],-1);
				p=fa[p];
			}break;
			default:{
				p=T[p].to[buf[i]-'a'];
				add(L[p],1);
			}break;
		}
}
int main(){
	root=++ncnt;
	fa[root]=0;
	for(int i=0;i<26;++i)T[0].to[i]=root;
	scanf("%s",buf);
	build();
	cook();
	for(int i=1;i<=ncnt;++i)
		FT.addEdge(T[i].fail,i);
	DFS(0);
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		Q.addEdge(v,u);
	}
	calc();
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}

