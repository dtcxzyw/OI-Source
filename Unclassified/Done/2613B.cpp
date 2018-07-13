#include <cstdio>
int A[5000];
bool check(int x,int n,int m){
	if(x<=0)return false;
	for(int i=0;i<n;++i){
		m-=A[i]/x;
		if(m<=0)return true;
	}
	return false;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int l=1,r=1;
	for(int i=0;i<n;++i){
		scanf("%d",&A[i]);
		if(A[i]>r)r=A[i];
	}
	int ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,n,m))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

