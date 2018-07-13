#include <cstdio>
struct Info{
	int l,r,w;
} P[200000];
typedef long double FT;
bool check(int n,FT v){
	FT ct=0.0;
	for(int i=0;i<n;++i){
		FT t=P[i].w/v;
		ct+=t;
		if(P[i].r<ct)
			return false;
		ct=(ct>P[i].l?ct:P[i].l);
	}
	return true;
}
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
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		P[i].l=read();
		P[i].r=read();
		P[i].w=read();
	}
	FT l=0.0L,r=1e7L;
	while(r-l>1e-3){
		FT mid=(l+r)/2.0;
		if(check(n,mid))r=mid;
		else l=mid;
	}
	printf("%.2Lf\n",l);
	return 0;
}

