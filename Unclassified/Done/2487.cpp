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
const int size=50010;
int timeStamp[size]={},t=0,siz,f[size];
double g[size];
void clear(){
	++t;
}
void add(int i,int fv,double gv){
	while(i<=siz){
		if(timeStamp[i]!=t)timeStamp[i]=t,f[i]=0,g[i]=0.0;
		if(fv>f[i])f[i]=fv,g[i]=gv;
		else if(fv==f[i])g[i]+=gv;
		i+=i&-i;
	}
}
void query(int i,int& fv,double& gv){
	while(i){
		if(timeStamp[i]==t){
			if(f[i]>fv)fv=f[i],gv=g[i];
			else if(f[i]==fv)gv+=g[i];
		}
		i-=i&-i;
	}
}
struct Info{
	int h,v,id;
	bool operator<(const Info& rhs) const{
		return h==rhs.h?v<rhs.v:h<rhs.h;
	}
} A[size],tmp[size]; 
struct Res{
	int dp[size];
	double cnt[size];
} b,e,*cur;
void merge(int l,int r){
	int m=(l+r)>>1;
	int lp=l,rp=m+1,pos=l;
	while(lp<=m || rp<=r){
		if(rp>r || (lp<=m && A[lp]<A[rp]))tmp[pos++]=A[lp++];
		else tmp[pos++]=A[rp++];
	}
	memcpy(A+l,tmp+l,sizeof(Info)*(r-l+1));
}
void solve(int l,int r){
	if(l==r){
		if(!cur->dp[l]){
			cur->dp[l]=1;
			cur->cnt[l]=1.0;
		}
	}
	else{
		int m=(l+r)>>1,pos=l;
		for(int i=l;i<=r;++i)
			if(A[i].id<=m)
				std::swap(A[i],A[pos++]);
		solve(l,m);
		clear();
		std::sort(A+m+1,A+r+1);
		for(int i=m+1,j=l;i<=r;++i){
			while(j<=m && A[j].h<=A[i].h){
				int id=A[j].id;
				add(A[j].v,cur->dp[id],cur->cnt[id]);
				++j;
			}
			int fv=0;
			double sum=0.0;
			query(A[i].v,fv,sum);
			if(fv>0){
				++fv;
				int id=A[i].id;
				if(fv>cur->dp[id])cur->dp[id]=fv,cur->cnt[id]=sum;
				else if(fv==cur->dp[id])cur->cnt[id]+=sum;
			}
		}
		solve(m+1,r);
		merge(l,r);
	}
}
int B[size];
bool cmp(const Info& lhs,const Info& rhs){
	return lhs.id>rhs.id;
}
double res[size];
int main(){
	int n=read();
	for(int i=n-1;i>=0;--i){
		A[i].h=read();
		B[i]=A[i].v=read();
		A[i].id=i;
	}
	std::sort(B,B+n);
	siz=std::unique(B,B+n)-B;
	for(int i=0;i<n;++i)
		A[i].v=std::lower_bound(B,B+siz,A[i].v)-B+1;
	//end=i
	cur=&e;
	solve(0,n-1);
	//begin=i
	std::sort(A,A+n,cmp);
	for(int i=0;i<n;++i)
		A[i].h=-A[i].h,A[i].v=siz-A[i].v+1,A[i].id=i;
	cur=&b;
	solve(0,n-1);
	//ans1
	int ans=0;
	double sum=0.0;
	for(int i=0;i<n;++i){
		int fi=e.dp[i];
		double gi=b.cnt[n-i-1]*e.cnt[i];
		if(fi>ans)ans=fi,sum=gi;
		else if(fi==ans)sum+=gi;
	}
	printf("%d\n",ans);
	//ans2
	for(int i=0;i<n;++i){
		int fi=b.dp[n-i-1]+e.dp[i]-1;
		if(fi==ans)res[i]=b.cnt[n-i-1]*e.cnt[i]/sum;
		else res[i]=0.0;
	}
	for(int i=n-1;i>=0;--i)printf("%.5lf ",res[i]);
	return 0;
}

