#include <cstdio>
#include <algorithm>
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
const int size=100100;
struct Info{
	int pos,val;
	bool operator<(Info rhs) const{
		return pos<rhs.pos;
	}
} A[size],B[size*2];
long long dp[2][2];
long long calcBit(int bit,int cnt){
	dp[0][1]=1LL<<60;
	dp[0][0]=0;
	for(int i=1;i<=cnt;++i){
		int now=i&1;
		int last=now^1;
		if(B[i].pos){
			int cb=(B[i].val>>bit)&1;
			dp[now][cb]=dp[last][0]+cb;
			dp[now][cb^1]=dp[last][1]+(cb^1);
		}
		else{
			int minv=std::min(dp[last][0],dp[last][1]);
			dp[now][0]=minv;
			dp[now][1]=minv+1;
		}
	}
	return std::min(dp[cnt&1][0],dp[cnt&1][1])<<bit;
}
int main(){
	int n=read();
	int m=read();
	A[0].pos=0;
	for(int i=1;i<=m;++i){
		A[i].pos=read();
		A[i].val=read();
	}
	std::sort(A,A+m+1);
	int cnt=0;
	for(int i=1;i<=m;++i){
		int delta=A[i].pos-A[i-1].pos-1;
		if(delta>=1)B[++cnt].pos=0;
		if(delta>=2)B[++cnt].pos=0;
		B[++cnt]=A[i];
	}
	long long res=0;
	for(int i=0;i<30;++i)
		res+=calcBit(i,cnt);
	printf("%lld\n",res);
	return 0;
}

