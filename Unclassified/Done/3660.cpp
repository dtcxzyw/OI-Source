#include <cstdio>
#include <algorithm>
int A[50001][2]={},id[50000];
bool cmp(int a,int b){
	return A[a][0]<A[b][0];
}
int sum[100001]={};
int add(int x,int n){
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
	int n,x;
	scanf("%d",&n);
	n<<=1;
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		if(A[x][0])A[x][1]=i;
		else A[x][0]=i;
	}	
	n>>=1;
	for(int i=1;i<=n;++i)
		id[i-1]=i;
	std::sort(id,id+n,cmp);
	int ans=0;
	for(int i=0;i<n;++i){
		x=id[i];
		ans+=query(A[x][1])-query(A[x][0]);
		add(A[x][1],n<<1);
	}
	printf("%d\n",ans);
	return 0;
}

