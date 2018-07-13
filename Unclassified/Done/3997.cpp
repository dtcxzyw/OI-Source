#include <cstdio>
#include <algorithm>
#include <vector>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100100;
int A[size]={};
void modify(int x,int val){
	while(x<size){
		A[x]+=val;
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=A[x];
		x-=x&-x;
	}
	return res;
}
int find(int p){
	int l=1,r=100000,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(query(mid)>=p)r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
int P[4*size],cnt=0;
std::vector<int> add[4*size],sub[4*size];
int getPos(int x){
	return std::lower_bound(P,P+cnt,x)-P;
}
struct Range{
	int r,b,e;
} R[2*size];
int siz=0;
void addR(int r,int b,int e){
	R[siz].r=r,R[siz].b=b,R[siz].e=e;
	++siz;
	P[cnt++]=b;
	P[cnt++]=e;
}
int main(){
	int n=read();
	int m=read();
	int k=read();
	for(int i=0;i<n;++i){
		int r=read();
		int a1=read();
		int a2=read();
		if(a1<=a2)addR(r,a1,a2);
		else addR(r,a1,m),addR(r,-m,a2);
	}
	std::sort(P,P+cnt);
	cnt=std::unique(P,P+cnt)-P;
	for(int i=0;i<siz;++i){
		add[getPos(R[i].b)].push_back(R[i].r);
		sub[getPos(R[i].e)].push_back(R[i].r);
	}
	long long ans=0,sum=0;
	for(int i=0;i<cnt-1;++i){
		for(int j=0;j<add[i].size();++j)
			modify(add[i][j],1);
		sum+=add[i].size();
		for(int j=0;j<sub[i].size();++j)
			modify(sub[i][j],-1);
		sum-=sub[i].size();
		if(sum>=k){
			long long r=find(sum-k+1),rad=P[i+1]-P[i];
			ans+=r*r*rad;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

