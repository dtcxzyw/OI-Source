#include <cstdio>
const int size=2000,mod=1000000007;
struct Node{
	int fail,next[10];
	bool flag;
} tree[size];
int ncnt=0;
char P[size],buf[size];
void insert(){
	int p=0;
	for(int i=0;buf[i];++i){
		int c=buf[i]-'0';
		if(!tree[p].next[c])tree[p].next[c]=++ncnt;
		p=tree[p].next[c];
	}
	tree[p].flag=true;
}
int q[size];
void cook(){
	int b=0,e=0;
	for(int i=0;i<10;++i)if(tree[0].next[i])q[e++]=tree[0].next[i];
	while(b!=e){
		int u=q[b++];
		tree[u].flag|=tree[tree[u].fail].flag;
		for(int i=0;i<10;++i){
			int& v=tree[u].next[i];
			if(v)tree[v].fail=tree[tree[u].fail].next[i],q[e++]=v;
			else v=tree[tree[u].fail].next[i];
		}
	}
}
void addm(int& a,int b){
	a=(a+b)%mod;
}
int f[size][size][2]={},g[size][size]={};
int main(){
	int m;
	scanf("%s%d",P,&m);
	for(int i=0;i<m;++i){
		scanf("%s",buf);
		insert();
	}
	cook();
	g[0][0]=f[0][0][1]=1;
	int siz;
	for(int i=0;P[i];++i){
		int c=P[i]-'0';
		siz=i+1;
		for(int j=0;j<=ncnt;++j)if(!tree[j].flag)
			for(int k=0;k<10;++k){
				int v=tree[j].next[k];
				if(!tree[v].flag && (i|k)){
					addm(g[i+1][v],g[i][j]);
					addm(f[i+1][v][0],f[i][j][0]);
					if(k<=c)addm(f[i+1][v][k==c],f[i][j][1]);
				}
			}
	}
	int ans=0;
	for(int i=1;P[i];++i)
		for(int j=0;j<=ncnt;++j)
			addm(ans,g[i][j]);
	for(int i=0;i<=ncnt;++i){
		addm(ans,f[siz][i][0]);
		addm(ans,f[siz][i][1]);
	}
	printf("%d\n",ans);
	return 0;
}

