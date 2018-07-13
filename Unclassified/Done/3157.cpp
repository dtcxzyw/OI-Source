#include <cstdio>
#include <cstring>
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
const int size=100005;
int n,S[size],now=0,timeStamp[size]={};
void clear(){
	++now;
}
void add(int x){
	while(x<=n){
		if(timeStamp[x]!=now)timeStamp[x]=now,S[x]=0;
		++S[x];
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		if(timeStamp[x]==now)res+=S[x];
		x-=x&-x;
	}
	return res;
}
struct Info{
	int t,p,val;
	bool side;//L R
	bool operator<(const Info& rhs) const{
		return p<rhs.p;
	}
} Op[size],P[size];
int cnt[size]={};
void solve(int l,int r){
	if(l<r){
		int m=(l+r)>>1;
		solve(l,m);
		solve(m+1,r);
		for(int i=l;i<=m;++i)Op[i].side=false;
		for(int i=m+1;i<=r;++i)Op[i].side=true;
		//merge
		int lp=l,rp=m+1,pos=l;
		while(pos<=r){
			if(rp>r || (lp<=m && Op[lp]<Op[rp]))P[pos++]=Op[lp++];
			else P[pos++]=Op[rp++];
		}
		//left
		clear();
		int num=0;
		for(int i=l;i<=r;++i)
			if(P[i].side)cnt[P[i].t]+=num-query(P[i].val);
			else add(P[i].val),++num;
		//right
		clear();
		for(int i=r;i>=l;--i)
			if(P[i].side)cnt[P[i].t]+=query(P[i].val);
			else add(P[i].val);
		//copy
		memcpy(Op+l,P+l,sizeof(Info)*(r-l+1));
	}
}
int A[size],B[size];
bool flag[size]={};
int main(){
	n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		B[A[i]]=i;	
	}
	int id=n;
	for(int i=1;i<=m;++i,--id){
		Op[id].t=id;
		int val=read();
		Op[id].p=B[val];
		flag[Op[id].p]=true;
		Op[id].val=val;
	}
	for(int i=1;i<=n;++i)
		if(!flag[i]){
			Op[id].t=id;
			Op[id].p=i;
			Op[id].val=A[i]; 
			--id;
		}
	solve(1,n);
	long long res=0;
	for(int i=1;i<=n;++i)res+=cnt[i];
	int end=n-m;
	for(int i=n;i>end;--i){
		printf("%lld\n",res);
		res-=cnt[i];
	}
	return 0;
}

