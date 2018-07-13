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
int A[100001];
long long S[100001];
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		S[i]=S[i-1]+A[i];
	}
	long long ans=0;
	for(int i=1;i<=n;++i){
		int l=i,r=i;
		while(l>1 && A[l-1]>=A[i])--l;
		while(r<n && A[r+1]>=A[i])++r;
		long long v=A[i]*(S[r]-S[l-1]);
		if(v>ans)ans=v;
	}
	printf("%lld\n",ans);
	return 0;
}
