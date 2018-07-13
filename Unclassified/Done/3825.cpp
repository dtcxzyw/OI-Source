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
int getAlpha(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c-'A';
}
const int size=50005,psiz=size*3;
struct G{
	struct Edge{
		int to,next;
	} E[4*size];
	int last[psiz],cnt;
	void clear(){
		memset(last,0,sizeof(last));
		cnt=0;
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
} g1,g2;
int sta[psiz],dfn[psiz],low[psiz],icnt,scnt,ccnt,col[psiz];
bool flag[psiz];
char buf[size];
void DFS(int u){
	dfn[u]=low[u]=++icnt;
	sta[++scnt]=u;
	flag[u]=true;
	for(int i=g1.last[u];i;i=g1.E[i].next){
		int v=g1.E[i].to;
		if(dfn[v]){
			if(flag[v] && low[u]>dfn[v])low[u]=dfn[v];
		}
		else {
			DFS(v);
			if(low[u]>low[v])low[u]=low[v];
		}
	}
	if(dfn[u]==low[u]){
		int c=++ccnt,v;
		do{
			v=sta[scnt--];
			flag[v]=false;
			col[v]=c;
		}while(u!=v);
	}
}
int d[psiz],q[psiz],state[psiz],op[psiz];
void color(int u){
	if(state[u]==0){
		state[u]=2,state[op[u]]=1;
		for(int i=g2.last[u];i;i=g2.E[i].next)
			color(g2.E[i].to);
	}
}
void solve(){
	memset(state,0,sizeof(state));
	int cnt=0;
	for(int i=1;i<=ccnt;++i)
		if(d[i]==0)
			q[++cnt]=i;
	for(int i=1;i<=cnt;++i){
		int u=q[i];
		for(int j=g2.last[u];j;j=g2.E[j].next){
			int v=g2.E[j].to;
			if(--d[v]==0)q[++cnt]=v;
		}
		color(op[u]);
	}
}
int get(int x,int t){
	return x*3+t;
}
int inv(int x,int t){
	return 3^buf[x]^t;
}
int input[size*2][4];
bool foo(int n,int m){
	memset(dfn,0,sizeof(dfn));
	memset(col,0,sizeof(col));
	icnt=scnt=ccnt=0;
	g1.clear();
	for(int i=0;i<m;++i){
		int u=input[i][0];
		int ut=input[i][1];
		if(buf[u]==ut)continue;
		int v=input[i][2];
		int vt=input[i][3];
		if(u==v){
			if(ut!=vt){
				g1.addEdge(get(u,ut),get(u,inv(u,ut)));
			}
		}
		else if(buf[v]==vt)g1.addEdge(get(u,ut),get(u,inv(u,ut)));
		else{
			g1.addEdge(get(u,ut),get(v,vt));
			g1.addEdge(get(v,inv(v,vt)),get(u,inv(u,ut)));
		}
	}
	for(int i=1,u=3;i<=n;++i)
		for(int j=0;j<3;++j,++u)
			if(j!=buf[i] && !dfn[u])
				DFS(u);
	g2.clear();
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;++i){
		int base=i*3;
		for(int j=0;j<3;++j)
			if(j!=buf[i]){
				int u=base+j;
				int v=base+inv(i,j);
				if(col[u]==col[v])return false;
				op[col[u]]=col[v];
				op[col[v]]=col[u];
				for(int k=g1.last[u];k;k=g1.E[k].next){
					int v=g1.E[k].to;
					if(col[u]!=col[v])
						g2.addEdge(col[v],col[u]),++d[col[u]];
				}
			}
	}
	solve();
	for(int i=1;i<=n;++i)
		for(int j=0;j<3;++j)
			if(j!=buf[i] && state[col[get(i,j)]]==1){
				putchar('A'+j);
				break;
			}
	putchar('\n');
	return true;
}
int pos[10];
int main(){
	int n=read();
	int d=read();
	scanf("%s",buf+1);
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(buf[i]=='x')
			pos[cnt++]=i;
	for(int i=1;i<=n;++i)buf[i]-='a';
	int m=read();
	for(int i=0;i<m;++i){
		input[i][0]=read();
		input[i][1]=getAlpha();
		input[i][2]=read();
		input[i][3]=getAlpha();
	}
	int end=1<<d;
	for(int i=0;i<end;++i){
		for(int j=0;j<d;++j)
			buf[pos[j]]=(i&(1<<j)?0:1);
		if(foo(n,m))return 0;
	}
	puts("-1");
	return 0;
}

