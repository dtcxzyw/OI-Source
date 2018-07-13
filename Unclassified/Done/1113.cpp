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
int dp[10001];
int main(){
	int n=read(),ans=0;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;++i){
		read();
		int len=read(),x,maxt=0;
		while(x=read())
			if(dp[x]>maxt)
				maxt=dp[x];
		dp[i]=maxt+len;
		if(dp[i]>ans)ans=dp[i];
	}
	printf("%d\n",ans);
	return 0;
}

