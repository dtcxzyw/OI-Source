#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=55,mod=65521;
struct Mat{
	unsigned int val[size][size];
	int n,m;
	Mat(int n,int m):n(n),m(m){
		memset(val,0,sizeof(val));
	}
	unsigned int* operator[](int id){
		return val[id];
	}
	const unsigned int* operator[](int id) const{
		return val[id];
	}
	Mat operator*(const Mat& rhs) const{
		Mat res(n,rhs.m);
		for(int i=0;i<n;++i)
			for(int j=0;j<rhs.m;++j){
				unsigned long long sum=0;
				for(int k=0;k<m;++k)
					sum+=val[i][k]*rhs[k][j];
				res[i][j]=sum%mod;
			}
		return res;
	}
};
int tmp[8],id[8];
bool flag[8];
int move(int state,int mask,int k,bool full){
	for(int i=k;i>=1;--i){
		tmp[i]=state%10;
		state/=10;
	}
	tmp[k+1]=6;
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=k;++i)
		if(mask&(1<<i)){
			if(flag[tmp[i]])return 0;
			flag[tmp[i]]=true;
		}
		
	for(int i=1;i<=k;++i)
		if(flag[tmp[i]])
			tmp[i]=6;
			
	if(!full){
		bool v=false;
		for(int i=2;i<=k+1;++i)
			if(tmp[i]==tmp[1]){
				v=true;
				break;
			}
		if(!v)return 0;
	}
	
	int cur=0;
	memset(id,0,sizeof(id));
	for(int i=2-full;i<=k+1;++i){
		if(!id[tmp[i]])id[tmp[i]]=++cur;
		tmp[i]=id[tmp[i]];
	}
	int s=0;
	for(int i=2-full;i<=k+1;++i)
		s=s*10+tmp[i];
	return s;
}
struct Set{
	int st[60],scnt;
	Set():scnt(0){}
	void DFS(int s,int d,int maxId){
		if(d==0)st[scnt++]=s;
		else{
			for(int i=1;i<=maxId+1;++i)
				DFS(s*10+i,d-1,std::max(maxId,i));
		}
	}
	int find(int s){
		return std::lower_bound(st,st+scnt,s)-st;
	}
} S[6];
int dp[10][71];
int main(){
	int k;
	long long n;
	scanf("%d%lld",&k,&n);
	for(int i=1;i<=k;++i)S[i].DFS(0,i,0);
	dp[1][0]=1;
	for(int i=2;i<=k;++i){
		int end=1<<(i-1);
		for(int j=0;j<S[i-1].scnt;++j)
			for(int l=0;l<end;++l){
				int dst=move(S[i-1].st[j],l<<1,i-1,true);
				if(dst==0)continue;
				int p=S[i].find(dst);
				dp[i][p]=(dp[i][p]+dp[i-1][j])%mod;
			}
	}
	n-=k;
	
	Mat res(1,S[k].scnt),mul(S[k].scnt,S[k].scnt);
	for(int i=0;i<S[k].scnt;++i)
		res[0][i]=dp[k][i];
	{
		int end=1<<k;
		for(int i=0;i<S[k].scnt;++i){
			for(int j=0;j<end;++j){
				int dst=move(S[k].st[i],j<<1,k,false);
				if(dst==0)continue;
				int p=S[k].find(dst);
				++mul[i][p];
			}
		}
	}
	
	while(n){
		if(n&1)res=res*mul;
		n>>=1,mul=mul*mul;
	}
	printf("%d\n",res[0][0]);
	return 0;
}

