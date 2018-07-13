#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100005;
int lb;
struct Fac{
	int val[5],id;
	bool operator<(const Fac& rhs) const{
		return val[lb]>rhs[lb];
	}
	int& operator[](int i){
		return val[i];
	}
	int operator[](int i) const{
		return val[i];
	}
	int calc(int s){
		int res=0;
		for(int i=0;i<=lb;++i)
			if(s&(1<<i))res+=val[i];
			else res-=val[i];
		return res;
	}
} A[size];
int C[5];
int main(){
	int n=read();
	int k=read();
	lb=k-1;
	for(int i=0;i<k;++i)C[i]=read();
	for(int i=0;i<n;++i){
		A[i].id=i+1;
		for(int j=0;j<k;++j)
			A[i][j]=read()*C[j];
		A[i][lb]=-A[i][lb];
	}
	std::sort(A,A+n);
	int ans=-1,a,b;
	int begin=1<<lb,end=1<<k;
	for(int i=begin;i<end;++i){
		int inv=i^(end-1);
		int maxv=A[0].calc(inv),cur=0;
		for(int j=1;j<n;++j){
			int val=A[j].calc(i);
			int res=val+maxv;
			if(res>ans)a=cur,b=j,ans=res;
			val=-val;
			if(val>maxv)maxv=val,cur=j;
		}
	}
	printf("%d %d\n%d\n",A[a].id,A[b].id,ans);
	return 0;
}

