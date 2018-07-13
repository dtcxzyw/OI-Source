#include <cstdio>
int A[100000];
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
bool check(int s,int n,int m){
	int cnt=0;
	for(int i=0;i<n;++i)
		if(cnt+A[i]>s){
			--m;
			cnt=A[i];
			if(!m)return false;
		}
		else cnt+=A[i];
	return true;
}
int main(){
	int n=read();
	int m=read();
	int l=0,r=0,ans=0;
	for(int i=0;i<n;++i){
		A[i]=read();
		r+=A[i];
		if(A[i]>l)l=A[i];
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,n,m))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}

