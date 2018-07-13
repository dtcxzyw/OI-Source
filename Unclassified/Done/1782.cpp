#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=10010;
long long dp[size]={},C,f[size];
void push(int v,long long w){
	for(int j=C;j>=v;--j){
		long long val=dp[j-v]+w;
		if(dp[j]<val)dp[j]=val;
	}
}
int main(){
	int n=read();
	int m=read();
	C=read();
	for(int i=1;i<=n;++i){
		int vi=read();
		int wi=read();
		int d=read();
		if(d*vi>C){
			for(int j=vi;j<=C;++j){
				long long val=dp[j-vi]+wi;
				if(dp[j]<val)dp[j]=val;
			}
		}
		else{
			for(int j=1;j<=d;j<<=1){
				push(vi*j,wi*j);
				d-=j;
			}
			if(d)push(vi*d,wi*d);
		}
	}

	for(int i=1;i<=m;++i){
		long long a=read();
		long long b=read();
		long long c=read();
		for(int j=0;j<=C;++j)f[j]=(a*j+b)*j+c;
		for(int j=C;j>=0;--j)
			for(int k=0;k<=j;++k){
				long long val=dp[j-k]+f[k];
				if(dp[j]<val)dp[j]=val;
			}
	}
	long long ans=0;
	for(int i=0;i<=C;++i)
		if(ans<dp[i])
			ans=dp[i];
	printf("%lld\n",ans);
	return 0;
}

