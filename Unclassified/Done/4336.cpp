#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
const int size=19,mod=1000000007;
long long inv(long long x){
	long long res=1;
	int k=mod-2;
	while(k){
		if(k&1)res=res*x%mod;
		k>>=1,x=x*x%mod;
	}
	return res;
}
int A[size][size];
int solve(int n){
	for(int i=1;i<=n;++i){
		int x=i;
		for(int j=i;j<=n;++j)
			if(A[j][i]){
				x=j;
				break;
			}
		if(x!=i){
			for(int j=i;j<=n;++j)
				std::swap(A[i][j],A[x][j]);
		}
		if(A[i][i]==0)
			return 0;
		long long invII=inv(A[i][i]);
		for(int j=i+1;j<=n;++j){
			long long mul=A[j][i]*invII%mod;
			for(int k=i;k<=n;++k)
				A[j][k]=(A[j][k]-A[i][k]*mul)%mod;
		}
	}
	long long res=1;
	for(int i=1;i<=n;++i)res=res*A[i][i]%mod;
	return res;
}
std::vector<std::pair<int,int> > E[size];
int main(){
	int n;
	scanf("%d",&n);
	--n;
	for(int i=0;i<n;++i){
		int m;
		scanf("%d",&m);
		E[i].resize(m);
		for(int j=0;j<m;++j)
			scanf("%d%d",&E[i][j].first,&E[i][j].second);
	}
	int end=1<<n,res=0;
	for(int i=0;i<end;++i){
		memset(A,0,sizeof(A));
		int bcnt=0;
		for(int j=0;j<n;++j)
			if(i&(1<<j)){
				for(int k=0;k<E[j].size();++k){
					int u=E[j][k].first,v=E[j][k].second;
					--A[u][v];
					++A[u][u];
					--A[v][u];
					++A[v][v];
				}
				++bcnt;
			}
		int val=solve(n);
		if((bcnt^n)&1)res=(res-val)%mod;
		else res=(res+val)%mod;
	}
	printf("%d\n",(res+mod)%mod);
	return 0;
}

