#include <cstdio>
#include <cstring>
const int size=31,mod=2017;
int n;
struct Mat{
	int v[size][size];
	Mat(){
		memset(v,0,sizeof(v));
	}
	Mat operator*(const Mat& rhs) const{
		Mat res;
		for(int i=0;i<=n;++i)
			for(int j=0;j<=n;++j)
				for(int k=0;k<=n;++k)
					res.v[i][j]=(res.v[i][j]+v[i][k]*rhs.v[k][j])%mod;
		return res;
	}
};
int main(){
	int m;
	scanf("%d%d",&n,&m);
	Mat res,mul;
	for(int i=0;i<=n;++i)
		res.v[i][i]=mul.v[i][i]=mul.v[i][0]=1;
	for(int i=0;i<m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		mul.v[u][v]=mul.v[v][u]=1;
	}
	int t;
	scanf("%d",&t);
	while(t){
		if(t&1)res=res*mul;
		t>>=1,mul=mul*mul;
	}
	int sum=0;
	for(int i=0;i<=n;++i)
		sum=(sum+res.v[1][i])%mod;
	printf("%d\n",sum);
	return 0;
}

