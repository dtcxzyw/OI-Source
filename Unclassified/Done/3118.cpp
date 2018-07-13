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
const int size=20;
int dp[1<<size]={},bcnt[1<<size],d[size];
int t[size][1001],siz[size];
int find(int i,int x){
	int l=1,r=siz[i],ans=-(1<<30); 
	while(l<=r){
		int mid=(l+r)>>1;
		if(t[i][mid]<=x)ans=t[i][mid],l=mid+1;
		else r=mid-1;
	}
	if(ans+d[i]>=x)return ans+d[i];
	return -(1<<30);
}
int main(){
	int n=read();
	int l=read();
	for(int i=0;i<n;++i){
		d[i]=read();
		siz[i]=read();
		for(int j=1;j<=siz[i];++j)t[i][j]=read();
	}
	int end=1<<n,ans=30;
	memset(dp,0xc0,sizeof(dp));
	dp[0]=0;
	for(int i=0;i<end;++i){
		bcnt[i]=bcnt[i>>1]+(i&1);
		if(dp[i]>=l && ans>bcnt[i])ans=bcnt[i]; 
		if(bcnt[i]+1<ans && dp[i]!=0xc0c0c0c0){
			for(int j=0;j<n;++j)
				if(!(i&(1<<j))){
					int dst=i|(1<<j);
					int val=find(j,dp[i]);
					if(dp[dst]<val)dp[dst]=val;
				}
		}
	}
	printf("%d\n",ans==30?-1:ans);
	return 0;
}

