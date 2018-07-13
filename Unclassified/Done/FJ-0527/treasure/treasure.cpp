#include <cstdio>
#include <cstring>
int link[13][13],n;
struct Info{
	int s,v,to;
	bool operator<(const Info& rhs) const{
		return v*s<rhs.v*rhs.s;
	}
} q[13];
bool flag[13]={};
void update(int u,int s){
	flag[u]=true;
	q[u].s=q[u].v=10000;
	for(int i=1;i<=n;++i)
		if(!flag[i] && link[u][i]!=0x3f3f3f3f){
			Info li;
			li.s=s+1,li.v=link[u][i],li.to=i;
			if(li<q[u])q[u]=li;
		}
}
int foo(int u){
	memset(flag,0,sizeof(flag));
	int w=0;
	update(u,0);
	for(int i=1;i<n;++i){
		Info mi;
		mi.s=mi.v=10000;
		int src;
		for(int j=1;j<=n;++j)
			if(flag[j] && !flag[q[j].to] && q[j]<mi)mi=q[j],src=j;
		w+=mi.s*mi.v;
		update(mi.to,mi.s);
		update(src,mi.s-1);
	}
	return w;
}
int main(){
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	int m;
	scanf("%d%d",&n,&m);
	memset(link,0x3f,sizeof(link));
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		if(link[u][v]>w)
			link[u][v]=link[v][u]=w;
	}
	int ans=1<<30;
	for(int i=1;i<=n;++i){
		int w=foo(i);
		if(ans>w)ans=w;
	}
	printf("%d\n",ans);
	return 0;
}

