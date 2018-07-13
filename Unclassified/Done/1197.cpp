#include <cstdio>
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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=400010;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int order[size]={},fa[size],ans[size],bcnt;
bool flag[size]={};
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int a,int b){
	a=find(a),b=find(b);
	if(a!=b){
		fa[a]=b;
		--bcnt;
	}
}
int main(){
	int n=read();
	int m=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	int k=read();
	for(int i=0;i<n;++i)
		fa[i]=i;
	for(int i=1;i<=k;++i){
		order[i]=read();
		flag[order[i]]=true;
	}
	
	bcnt=n-k;
		
	for(int i=0;i<n;++i)
		if(!flag[i]){
			for(int j=last[i];j;j=E[j].next){
				int v=E[j].to;
				if(!flag[v])merge(i,v);
			}
		}
		
	ans[k+1]=bcnt;
	for(int i=k;i>=1;--i){
		int u=order[i];
		++bcnt;
		flag[u]=false;
		for(int j=last[u];j;j=E[j].next){
			int v=E[j].to;
			if(!flag[v])merge(u,v);
		}
		ans[i]=bcnt;
	}
	
	for(int i=1;i<=k+1;++i)
		print(ans[i]);
	return 0;
}

