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
const int size=5001;
int A[size*size],P[size*size],L[size],R[size];
int main(){
	long long x=read();
	long long a=read();
	long long b=read();
	long long c=read();
	long long d=read();
	int n=read();
	int m=read();
	int siz=n*m;
	for(int i=1;i<=siz;++i)A[i]=i;
	for(int i=1;i<=siz;++i){
		x=(((a*x+b)*x)+c)%d;
		std::swap(A[i],A[x%i+1]);
	}
	int q=read();
	for(int i=0;i<q;++i)
		std::swap(A[read()],A[read()]);
	for(int i=1;i<=siz;++i)
		P[A[i]]=i;
	for(int i=1;i<=n;++i)L[i]=1,R[i]=m;
	int num=n+m-1;
	for(int i=1;num;++i){
		int p=P[i]-1;
		int px=p/m+1,py=p%m+1;
		if(L[px]<=py && py<=R[px]){
			printf("%d ",i);
			for(int j=px+1;j<=n;++j)
				if(L[j]<py)L[j]=py;
				else break;
			for(int j=px-1;j>=1;--j)
				if(R[j]>py)R[j]=py;
				else break;
			--num;
		}
	}
	puts("");
	return 0;
} 

