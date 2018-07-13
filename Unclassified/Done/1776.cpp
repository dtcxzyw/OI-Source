#include <cstdio>
const int size=100010;
int v[size],w[size],dp[size]={};
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
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n,W;
	n=read();
	W=read();
	int a,b,c,cnt=0;
	for(int i=0;i<n;++i){
		a=read();
		b=read();
		c=read();
		for(int j=1;j<=c;j<<=1){
			v[cnt]=a*j,w[cnt]=b*j;
			c-=j,++cnt;
		}	
		if(c){
			v[cnt]=a*c,w[cnt]=b*c;
			++cnt;
		}
	}
	for(int i=0;i<cnt;++i)
		for(int j=W;j>=w[i];--j)
			CAS(dp[j],dp[j-w[i]]+v[i]);
	printf("%d\n",dp[W]);
	return 0;
}

