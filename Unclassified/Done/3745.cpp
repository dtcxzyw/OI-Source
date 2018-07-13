#include <cstdio>
typedef long long Int64;
Int64 read(){
	Int64 res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
Int64 maxv(Int64 a,Int64 b){
	return a>b?a:b;
}
Int64 minv(Int64 a,Int64 b){
	return a<b?a:b;
}
const int size=100100;
Int64 t[size],b[size],A,B,C,n,m;
Int64 calcS(Int64 x){
	Int64 res=0;
	for(int i=1;i<=n;++i)
		if(t[i]<x)
			res+=x-t[i];
	return res*C;
}
Int64 calcT(Int64 x){
	Int64 l=0,r=0;
	for(int i=1;i<=m;++i)
		if(b[i]<x)l+=x-b[i];
		else r+=b[i]-x;
	if(A<B){
		Int64 mv=minv(l,r);
		return mv*A+(r-mv)*B;
	}
	else return r*B;
}
int main(){
	A=read();
	B=read();
	C=read();
	n=read();
	m=read();
	Int64 l=1<<30,r=0;
	for(int i=1;i<=n;++i){
		t[i]=read();
		l=minv(l,t[i]);
	}
	for(int i=1;i<=m;++i){
		b[i]=read();
		r=maxv(r,b[i]);
	}
	Int64 ans;
	if(C>100000)ans=calcT(l);
	else{
		while(r-l>=6){
			Int64 lm=(2*l+r)/3,rm=(l+2*r)/3;
			if(calcS(lm)+calcT(lm)<calcS(rm)+calcT(rm))r=rm;
			else l=lm;
		}
		ans=1LL<<62;
		for(Int64 i=l;i<=r;++i)
			ans=minv(ans,calcS(i)+calcT(i));
	}
	printf("%lld\n",ans);
	return 0;
}

