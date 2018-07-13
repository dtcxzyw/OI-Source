#include <cstdio>
#include <algorithm>
#include <cstring>
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
int getAlpha(){
	int c;
	do c=getchar();
	while(c!='A' && c!='B');
	return c;
}
int iabs(int x){
	return x>0?x:-x;
}
const int size=100005;
int A[size][2];
long long calc1(int cnt){
	int *B=A[0],end=cnt*2,mid=cnt-1;
	std::nth_element(B,B+mid,B+end);
	long long res=0;
	for(int i=0;i<cnt;++i)res-=B[i];
	for(int i=cnt;i<end;++i)res+=B[i];
	return res;
}
int B[size*2];
struct Seg{
	long long sum[size<<3];
	int siz[size<<3];
	Seg(){
		memset(sum,0,sizeof(sum));
		memset(siz,0,sizeof(siz));
	}
	#define ls l,m,id<<1
	#define rs m+1,r,id<<1|1
	void modify(int l,int r,int id,int op,int p){
		siz[id]+=op;
		sum[id]+=op*B[p-1];
		if(l!=r){
			int m=(l+r)>>1;
			if(p<=m)modify(ls,op,p);
			else modify(rs,op,p);
		}
	}
	int querySize(int l,int r,int id,int nl,int nr){
		if(nl<=l && r<=nr)return siz[id];
		else{
			int m=(l+r)>>1,res=0;
			if(nl<=m)res+=querySize(ls,nl,nr);
			if(m<nr)res+=querySize(rs,nl,nr);
			return res;
		}
	}
	long long querySum(int l,int r,int id,int nl,int nr){
		if(nl<=l && r<=nr)return sum[id];
		else{
			int m=(l+r)>>1;
			long long res=0;
			if(nl<=m)res+=querySum(ls,nl,nr);
			if(m<nr)res+=querySum(rs,nl,nr);
			return res;
		}
	}
	int queryKth(int l,int r,int id,int k){
		if(l==r)return l;
		else{
			int m=(l+r)>>1,lsiz=siz[id<<1];
			if(k<=lsiz)return queryKth(ls,k);
			return queryKth(rs,k-lsiz);
		}
	}
	long long solve(int siz,int n){
		if(siz){
			int p=queryKth(1,n,1,siz);
			long long vl=static_cast<long long>(B[p-1])*querySize(1,n,1,1,p)-querySum(1,n,1,1,p);
			long long vr=querySum(1,n,1,p+1,n)-static_cast<long long>(B[p-1])*querySize(1,n,1,p+1,n);
			return vl+vr;
		}
		return 0;
	}
	#undef ls
	#undef rs
} TL,TR;
bool cmp(int a,int b){
	return A[a][0]+A[a][1]<A[b][0]+A[b][1];
}
int id[size];
long long calc2(int cnt){
	memcpy(B,A,sizeof(A));
	std::sort(B,B+cnt*2);
	int siz=std::unique(B,B+cnt*2)-B;
	for(int i=0;i<cnt;++i)id[i]=i;
	std::sort(id,id+cnt,cmp);
	for(int i=0;i<cnt;++i)
		for(int j=0;j<2;++j)
			A[i][j]=std::lower_bound(B,B+siz,A[i][j])-B+1;
	for(int i=0;i<cnt;++i){
		int u=id[i];
		TR.modify(1,siz,1,1,A[u][0]);
		TR.modify(1,siz,1,1,A[u][1]);  
	}
	long long ans=1LL<<60;
	//L [0,i) R [i,cnt)
	for(int i=0;i<=cnt;++i){
		int lsiz=i,rsiz=cnt-i;
		long long val=TL.solve(lsiz,siz)+TR.solve(rsiz,siz);
		ans=std::min(ans,val);
		if(i<cnt){
			int u=id[i];
			TR.modify(1,siz,1,-1,A[u][0]);
			TR.modify(1,siz,1,-1,A[u][1]); 
			TL.modify(1,siz,1,1,A[u][0]);
			TL.modify(1,siz,1,1,A[u][1]); 
		}
	}
	return ans;
}
int main(){
	int k=read();
	int n=read();
	long long ans=0;
	int cnt=0;
	for(int i=0;i<n;++i){
		int pa=getAlpha();
		int qa=read();
		int pb=getAlpha();
		int qb=read();
		if(pa==pb)ans+=iabs(qa-qb);
		else{
			A[cnt][0]=qa,A[cnt][1]=qb;
			++cnt;
		}
	}
	ans+=cnt+(k==1?calc1(cnt):calc2(cnt));
	printf("%lld\n",ans);
	return 0;
}

