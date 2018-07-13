#include <cstdio>
#include <cstring>
const int mod=45989;
struct Edge{
	int src,dst;
} E[121];
int cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].dst=v,E[cnt].src=u;
}
struct Mat{
	int data[121][121];
	Mat(){
		memset(data,0,sizeof(data));
	}
	Mat operator*(const Mat& rhs) const{
		Mat res;
		for(int i=0;i<=cnt;++i)
			for(int j=0;j<=cnt;++j){
				for(int k=0;k<=cnt;++k)
					res.data[i][j]+=data[i][k]*rhs.data[k][j]%mod;
				res.data[i][j]%=mod;
			}
		return res;
	}
};
int main(){
	int n,m,t,a,b;
	scanf("%d%d%d%d%d",&n,&m,&t,&a,&b);
	Mat res,mul;
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	for(int i=1;i<=cnt;++i)
		if(E[i].src==a)
			res.data[0][i]=1;
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
			if(E[i].dst==E[j].src && ((i-1)>>1)!=((j-1)>>1))
				mul.data[i][j]=1;
	--t;
	while(t){
		if(t&1)res=res*mul;
		t>>=1,mul=mul*mul;
	}
	int ans=0;
	for(int i=1;i<=cnt;++i)
		if(E[i].dst==b)
			ans=(ans+res.data[0][i])%mod;
	printf("%d\n",ans);
	return 0;
}

