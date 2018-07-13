#include <cstdio>
#include <cstring>
const int size=120001;
bool dp[size];
int num[7],w[100];
bool check(){
	int sum=0,cnt=0;
	for(int i=1;i<=6;++i)
		sum+=i*num[i];
	if(sum&1)return false;
	for(int i=1;i<=6;++i){
		for(int j=1;j<=num[i];j<<=1){
			w[++cnt]=i*j;
			num[i]-=j;
		}
		if(num[i])w[++cnt]=i*num[i];
	}
	memset(dp,0,sizeof(dp));
	dp[0]=true;
	sum>>=1;
	for(int i=1;i<=cnt;++i){
		for(int j=sum;j>=w[i];--j)
			dp[j]|=dp[j-w[i]];
		if(dp[sum])return true;
	}
	return false;
}
bool foo(int id){
	bool flag=true;
	for(int i=1;i<=6;++i){
		scanf("%d",&num[i]);
		if(num[i]!=0)flag=false;
	}
	if(flag)return false;
	printf("Collection #%d:\n",id);
	puts(check()?"Can be divided.":"Can't be divided.");
	puts("");
	return true;
}
int main(){
	int i=1;
	while(foo(i))++i;
	return 0;
}

