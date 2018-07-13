#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int size=20005,inf=1000000005;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int minv[size<<2],offset[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int nr,val;
void modify(int l,int r,int id){
	if(r<=nr)minv[id]+=val,offset[id]+=val;
	else{
		int m=(l+r)>>1;
		modify(ls);
		if(m<nr)modify(rs);
		minv[id]=std::min(minv[id<<1],minv[id<<1|1])+offset[id];
	}
}
int query(int l,int r,int id){
	if(r<=nr)return minv[id];
	else{
		int m=(l+r)>>1,res=inf;
		res=std::min(res,query(ls));
		if(m<nr)res=std::min(res,query(rs));
		return res+offset[id];
	}
}
int d[size],c[size],s[size],w[size],L[size],R[size],dp[size];
void build(int l,int r,int id){
	if(l==r)minv[id]=dp[l];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		minv[id]=std::min(minv[id<<1],minv[id<<1|1]);
	}
}
int main(){
	int n=read();
	int k=read();
	d[1]=0;
	for(int i=2;i<=n;++i)d[i]=read();
	for(int i=1;i<=n;++i)c[i]=read();
	for(int i=1;i<=n;++i)s[i]=read();
	for(int i=1;i<=n;++i)
		w[i]=read();
	++n,++k;
	d[n]=inf,w[n]=inf,c[n]=0,s[n]=0;
	for(int i=1;i<=n;++i){
		L[i]=std::lower_bound(d+1,d+n+1,d[i]-s[i])-d;
		R[i]=std::upper_bound(d+1,d+n+1,d[i]+s[i])-d-1;
		addEdge(R[i],i);
	}
	
	int cur=0;
	for(int i=1;i<=n;++i){
		dp[i]=cur+c[i];
		for(int j=last[i];j;j=E[j].next)
			cur+=w[E[j].to];
	}
	int ans=dp[n];
	for(int i=2;i<=k;++i){
		memset(offset,0,sizeof(offset));
		build(1,n,1);
		for(int j=1;j<=n;++j){
			nr=j-1;
			dp[j]=c[j]+(nr?query(1,n,1):0);
			for(int e=last[j];e;e=E[e].next){
				int v=E[e].to;
				nr=L[v]-1;
				val=w[v];
				if(nr)modify(1,n,1);
			}
		}
		ans=std::min(ans,dp[n]);
	}
	printf("%d\n",ans);
	return 0;
}

