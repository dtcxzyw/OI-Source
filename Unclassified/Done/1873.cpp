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
int A[1000000];
bool check(int x,int n,int m){
	for(int i=0;i<n;++i)
		if(A[i]>x && (m-=A[i]-x)<=0)
			return true;
	return false;
}
int main(){
	int n,m;
	n=read();
	m=read();
	int l=0,r=0;
	for(int i=0;i<n;++i){
		A[i]=read();
		if(A[i]>r)r=A[i];
	}
	int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,n,m))l=mid+1,ans=(ans>mid?ans:mid);
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

