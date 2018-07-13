#include <cstdio>
#include <algorithm>
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
const int size=200005;
const long long inf=1LL<<50;
class ST{
private:
	static int logv[size],bin[18];
public:
	static void init(int n){
		logv[1]=0;
		for(int i=2;i<=n;++i)
			logv[i]=logv[i>>1]+1;
		for(int i=0;i<18;++i)bin[i]=1<<i;
	}
	long long val[size][18];
	void build(int n){
		for(int i=1;i<=logv[n];++i)
			for(int j=1;j<=n;++j)
				val[j][i]=std::min(val[j][i-1],val[j+bin[i-1]][i-1]);
	}
	long long query(int l,int r){
		int p=logv[r-l+1];
		return std::min(val[l][p],val[r-bin[p]+1][p]);
	}
} st[2];
int ST::logv[size],ST::bin[18];
long long S[size];
struct Info{
	int p,l;
	bool operator<(Info rhs) const{
		return p<rhs.p;
	}
} A[size];
long long SA[size],SS[size];
int pos[size];
int lower(int x,int k){
	int l=1,r=k,res=k+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(pos[mid]<x)l=mid+1;
		else r=mid-1,res=mid;
	}
	return res;
}
int upper(int x,int k){
	int l=1,r=k,res=k+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(pos[mid]<=x)l=mid+1;
		else r=mid-1,res=mid;
	}
	return res;
}
long long foo(int n){
	int k=read();
	for(int i=1;i<=k;++i){
		A[i].p=read();
		A[i].l=read();
	}
	std::sort(A+1,A+k+1);
	for(int i=1;i<=k;++i){
		st[0].val[i][0]=SS[i]=A[i].l-S[A[i].p];
		st[1].val[i][1]=SA[i]=A[i].l+S[A[i].p];	
	}
	st[0].build(k);
	st[1].build(k);
	for(int i=1;i<=k;++i)
		pos[i]=A[i].p;
	long long res=0;
	for(int i=1;i<=k;++i){
		int l=A[i].p,r=A[i].p;
		{
			int cl=1,cr=A[i].p-1;
			while(cl<=cr){
				int mid=(cl+cr)>>1;
				long long dis=SA[i]-S[mid],dl=inf,dr=inf;
				printf("dis %d ",(int)dis);
				
				int offset=A[i].p-mid;
				int ll=lower(std::max(1,mid-offset),k);
				int lr=upper(mid,k)-1;
				if(ll<=lr)dl=st[0].query(ll,lr)+S[mid];
				printf("ll %d lr %d ",ll,lr);
				int rl=lower(mid,k);
				int rr=upper(A[i].p-1,k)-1;
				if(rl<=rr)dr=st[1].query(rl,rr)-S[mid];
				printf("rl %d rr %d\n",rl,rr);
				if(dl>dis && dr>dis)l=mid,cr=mid-1;
				else cl=mid+1;
			}
		}
		{
			int cl=A[i].p+1,cr=n;
			while(cl<=cr){
				int mid=(cl+cr)>>1;
				long long dis=SS[i]+S[mid],dl=inf,dr=inf;
								printf("dis %d ",(int)dis);
				int ll=lower(A[i].p+1,k);
				int lr=upper(mid,k)-1;
				if(ll<=lr)dl=st[0].query(ll,lr)+S[mid];
							printf("ll %d lr %d ",ll,lr);
				int rp=mid+(mid-A[i].p);
				int rl=lower(mid,k);
				int rr=upper(std::min(rp-1,n),k)-1;
				if(rl<=rr)dr=st[1].query(rl,rr)-S[mid];
								printf("rl %d rr %d\n",rl,rr);
				if(rp<=n){
					int p=upper(rp,k)-1;
					if(pos[p]==rp)
						dr=std::min(dr,SA[p]-S[mid]+1);
				}
				
				if(dl>dis && dr>dis)r=mid,cl=mid+1,puts("XX");
				else cr=mid-1;
				
			}
		}
		res+=r-l+1;
		printf("%d %d %d\n",i,l,r);
	}
	return res;
}
int main(){
	int n=read();
	ST::init(n);
	int m=read();
	for(int i=2;i<=n;++i)S[i]=S[i-1]+read();
	for(int i=1;i<=m;++i)printf("%lld\n",foo(n));
	return 0;
}

