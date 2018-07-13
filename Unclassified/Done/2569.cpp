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
int maxv(int a,int b){
	return a>b?a:b;
}
const int size=2010;
int dp[size][size],q[size];
int main(){
	int t=read();
	int p=read();
	int w=read();
	memset(dp,0xc0,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=t;++i){
		int ap=read();
		int bp=read();
		int as=read();
		int bs=read();
		for(int j=0;j<=as;++j)dp[i][j]=-ap*j;
		for(int j=0;j<=p;++j)dp[i][j]=maxv(dp[i][j],dp[i-1][j]);
		if(i>w){
			int last=i-w-1,b,e;
			b=e=0;
			for(int j=0;j<=p;++j){
				while(b<e && q[b]<j-as)++b;
				int now=dp[last][j]+ap*j;
				while(b<e && dp[last][q[e-1]]+ap*q[e-1]<=now)--e;
				q[e++]=j;
				if(b<e)dp[i][j]=maxv(dp[i][j],dp[last][q[b]]-ap*(j-q[b]));
			}
			b=e=0;
			for(int j=p;j>=0;--j){
				while(b<e && q[b]>j+bs)++b;
				int now=dp[last][j]+bp*j;
				while(b<e && dp[last][q[e-1]]+bp*q[e-1]<=now)--e;
				q[e++]=j;
				if(b<e)dp[i][j]=maxv(dp[i][j],dp[last][q[b]]+bp*(q[b]-j));
			}
		}
	}
	int res=0;
	for(int i=0;i<=p;++i)
		res=maxv(res,dp[t][i]);
	printf("%d\n",res);
	return 0;
}

