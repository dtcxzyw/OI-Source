#include <cstdio>
#include <algorithm>
const int size=1<<20;
typedef long long Int64;
void FWT(Int64* A,int n){
	for(int i=2;i<=n;i<<=1){
		int m=i>>1;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<m;++k){
				Int64 t=A[j+k+m];
				A[j+k+m]=A[j+k]-t;
				A[j+k]+=t;
			}
		}
	}
}
void UFWT(Int64* A,int n){
	for(int i=2;i<=n;i<<=1){
		int m=i>>1;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<m;++k){
				Int64 t=A[j+k+m];
				A[j+k+m]=(A[j+k]-t)>>1;
				A[j+k]=(A[j+k]+t)>>1;
			}
		}
	}
}
Int64 a[size]={},b[size];
int st[size]={};
char buf[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%s",buf);
		for(int j=0;j<m;++j)
			st[j]=st[j]<<1|(buf[j]=='1');
	}
	for(int i=0;i<m;++i)++a[st[i]];
	int end=1<<n;
	b[0]=0;
	for(int i=1;i<end;++i)
		b[i]=b[i>>1]+(i&1);
	for(int i=0;i<end;++i)
		b[i]=std::min(b[i],n-b[i]);
	FWT(a,end);
	FWT(b,end);
	for(int i=0;i<end;++i)
		a[i]*=b[i];
	UFWT(a,end);
	Int64 res=n*m;
	for(int i=0;i<end;++i)
		res=std::min(res,a[i]);
	printf("%lld\n",res);
	return 0;
}

