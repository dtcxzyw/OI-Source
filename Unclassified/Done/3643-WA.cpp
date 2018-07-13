#include <cstdio>
#include <map>
#include <algorithm>
const int size=520,mod=1000000007;
int A[size],B[size],X[4*size];
int get(int x,int siz){
	return std::lower_bound(X,X+siz,x)-X;
}
std::map<int,int> dp[size]; 
typedef std::map<int,int>::iterator IterT;
int main(){
	int n;
	scanf("%d",&n);
	int siz=0;
	X[siz++]=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&A[i],&B[i]);
		X[siz++]=A[i];
		X[siz++]=A[i]+1;
		X[siz++]=B[i];
		X[siz++]=B[i]+1;
	}
	std::sort(X,X+siz);
	siz=std::unique(X,X+siz)-X;
	for(int i=1;i<=n;++i)A[i]=get(A[i],siz),B[i]=get(B[i],siz);
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j)
			for(IterT it=dp[j].begin();it!=dp[j].end();++it){
				int b=std::max(it->first+1,A[i]);
				for(int k=b;k<=B[i];++k){
					long long delta=X[b+1]-X[b];
					int& res=dp[i][k];
					res=(delta*it->second+res)%mod;
				}
			}
	}
	long long ans=0;
	for(int i=1;i<=n;++i)
		for(IterT it=dp[i].begin();it!=dp[i].end();++it){
			long long delta=X[it->first+1]-X[it->first];
			ans=(ans+delta*it->second)%mod;
		}
	printf("%lld\n",ans);
	return 0;
}

