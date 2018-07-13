#include <cstdio>
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
const int size=250000,mod=1000000007;
int A[size],dp[size]={},p[size]={};
int main(){
    int n=read();
    for(int i=1;i<=n;++i){
    	A[i]=read();
    	p[A[i]]=i;
    }
    int ans=0;
    for(int i=1;i<=n;++i){
    	ans=(ans+dp[A[i]])%mod;
    	++dp[A[i]];
        for(int j=(A[i]-1)&A[i];j;j=(j-1)&A[i])
        	if(p[j]>i)
            	dp[j]=(dp[A[i]]+dp[j])%mod;
    }
    printf("%d\n",ans);
    return 0;
}

