#include <cstdio>
#include <cstring>
long long mat[201][201],sum[201];
void CAS(int& a,int b){
	if(a<b)a=b;
}
bool check(int mid,int m){
	long long minv=0;
	for(int i=mid;i<=m;++i){
		if(sum[i-mid]<minv)minv=sum[i-mid];
		if(sum[i]>minv)return true;
	}
	return false;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int x,cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			scanf("%d",&x);
			mat[i][j]=mat[i][j-1]+x;
		}
		
	int ans=0;
	for(int i=1;i<=n;++i){
		memset(sum,0,sizeof(sum));
		for(int j=i;j<=n;++j){
			for(int k=1;k<=m;++k)sum[k]+=mat[j][k];
			int l=1,r=m;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check(mid,m))l=mid+1,CAS(ans,(j-i+1)*mid);
				else r=mid-1;
			}
		}
	}
	
	printf("%d\n",ans);
	return 0;
}

