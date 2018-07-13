#include <cstdio>
#include <cstring>
char buf[60];
int num[60],cnt[10];
long long dp[60][2]={},C[60][60];
int main(){
	scanf("%s",buf);
	int len=strlen(buf);
	for(int i=0;i<len;++i)
		++cnt[num[i+1]=buf[i]-'0'];
	C[0][0]=1;
	for(int i=1;i<=len;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	long long ans=0;
	for(int i=1;i<=len;++i){
		for(int j=0;j<num[i];++j)
			if(cnt[j]){
				--cnt[j];
				int sum=len-i;
				long long val=1;
				for(int k=0;k<10;++k){
					val*=C[sum][cnt[k]];
					sum-=cnt[k];
				}
				ans+=val;
				++cnt[j];
			}
		--cnt[num[i]];
	}
	printf("%lld\n",ans);
	return 0;
}

