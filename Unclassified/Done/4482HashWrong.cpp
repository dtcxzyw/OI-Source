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
const int size=100005,mod[3]={998244353,1000000007,2147483647},k=131;
long long calcInv(long long a,int mid){
	long long res=1,p=mod[mid];
	int k=p-2;
	while(k){
		if(k&1)res=res*a%p;
		k>>=1,a=a*a%p;
	}
	return res;
}
int inv[3][size],hash[3][size]={},n;
char buf[size];
#define asInt64(x) static_cast<long long>(x)
long long calc(int l,int r,int i){
	return asInt64(hash[i][r]-hash[i][l-1])*inv[i][l];
}
bool check(int l,int r,int x){
	for(int i=0;i<3;++i)
		if((calc(l,l+x-1,i)-calc(r-x+1,r,i))%mod[i])
			return false;
	return true;
}
int main(){
	int q;
	scanf("%s%d",buf+1,&q);
	n=strlen(buf+1);
	for(int i=0;i<3;++i){
		inv[i][0]=1;
		long long invv=calcInv(k,i);
		for(int j=1;j<=n;++j)
			inv[i][j]=inv[i][j-1]*invv%mod[i];
		for(int j=1;j<=n;++j)
			hash[i][j]=(asInt64(hash[i][j-1])*k+buf[j])%mod[i];
	}
	for(int i=0;i<q;++i){
		int b=read();
		int e=read();
		int l=1,r=e-b+1,ans=0;
		while(l<=r){
			int m=(l+r)>>1;
			if(check(b,e,m))l=m+1,ans=m;
			else r=m-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

