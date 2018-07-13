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
int v[1001][1001],c[1001];
void CAS(int& a,int b){
	if(a<b)a=b;
}
void sub(int& a,int n){
	a--;
	if(a<0)a=n-1;
}
int dp[1001];
int main(){
	int n=read();
	int m=read();
	int q=read();
	for(int i=0;i<n;++i)
		for(int j=1;j<=m;++j)
			v[i][j]=read();
			
	for(int i=0;i<n;++i)
		c[i]=read();
		
	memset(dp,0xc0,sizeof(dp));
	dp[0]=0;
		
	for(int i=1;i<=m;++i)
		for(int j=0;j<n;++j){
			int cu=j;
			sub(cu,n);
			int off=v[cu][i];
			for(int k=1;k<=q && k<=i;++k){
				CAS(dp[i],dp[i-k]+off-c[cu]);
				sub(cu,n);
				off+=v[cu][i-k];
			}
		}
			
	printf("%d\n",dp[m]);
	return 0;
}

