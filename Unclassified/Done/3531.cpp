#include <cstdio>
const int size=1000001;
char A[size],B[size];
int q[26][size],e[26]={},b[26]={},num[size],sum[size];
void add(int x,int n){
	while(x<=n){
		++sum[x];
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=sum[x];
		x-=x&-x;
	}
	return res;
}
int main(){
	int n;
	scanf("%d%s%s",&n,A,B);
	for(int i=0;i<n;++i){
		int a=A[i]-'A';
		q[a][e[a]++]=i;
	}
	for(int i=0;i<n;++i){
		int a=B[i]-'A';
		num[i+1]=q[a][b[a]++]+1;
	}
	long long ans=0;
	for(int i=1;i<=n;++i){
		add(num[i],n);
		ans+=i-query(num[i]);
	}
	printf("%lld\n",ans);
	return 0;
}

