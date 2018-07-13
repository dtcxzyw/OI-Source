#include <cstdio>
int n,k,len[10000];
bool check(int x){
	if(x==0)return false;
	int cnt=k;
	for(int i=0;i<n && cnt>0;++i)
		cnt-=len[i]/x;
	return cnt<=0;
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	scanf("%d%d",&n,&k);
	double x;
	int l=0,r=0,ans=0;
	for(int i=0;i<n;++i){
		scanf("%lf",&x);
		len[i]=x*100.0;
		CAS(r,len[i]);
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,CAS(ans,mid);
		else r=mid-1;
	}
	int a=ans/100;
	int b=(ans%100)/10;
	int c=ans%10;
	printf("%d.%d%d",a,b,c);
	return 0;
}

