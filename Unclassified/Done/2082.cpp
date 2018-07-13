#include <cstdio>
#include <algorithm>
struct Line{
	long long l,r;
	bool operator<(const Line& rhs) const{
		return l<rhs.l;
	}
} L[100000];
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		L[i].l=read();
		L[i].r=read();
	}
	std::sort(L,L+n);
	long long sum=0,B=0,E=-1;
	for(int i=0;i<n;++i)
		if(L[i].l<=E)E=std::max(E,L[i].r);
		else{
			sum+=E-B+1;
			B=L[i].l,E=L[i].r;
		}
	printf("%lld\n",sum+E-B+1);
	return 0;
}

