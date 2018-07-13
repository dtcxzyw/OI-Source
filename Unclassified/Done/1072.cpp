#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxv=2000000001;
struct Range{
    int l,r;
    Range(int l_,int r_):l(l_),r(r_){}
    void operator&=(Range rhs){
        l=max(l,rhs.l),r=min(r,rhs.r);
    }
};
const int psiz=50000;
int prime[psiz],cnt=0;
bool test(int x){
	for(int i=0;i<cnt;++i)
		if(x%prime[i]==0)return false;
	return true;
}
void calcPrime(){
	for(int i=2;i<=psiz;++i)
		if(test(i))
			prime[cnt++]=i;
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
int fac[10000],fcnt;
void cut(int x){
	for(int i=0;i<cnt && x>1 && x>=prime[i];++i)
		if(x%prime[i]==0){
			do x/=prime[i];
			while(x%prime[i]==0);
			fac[fcnt++]=prime[i];
		}
	if(x>1)fac[fcnt++]=x;
}
int foo(){
	int a,b,c,d;
	a=read();
	b=read();
	c=read();
	d=read();
	if(a%b!=0 || d%c!=0)
	    return 0;
	int ca,cb,cc,cd,p,ans=1;
	bool flag=false;
	fcnt=0;
	cut(a);cut(b);cut(c);cut(d);
	std::sort(fac,fac+fcnt);
	fcnt=std::unique(fac,fac+fcnt)-fac;
	for(int i=0;i<fcnt;++i){
		Range range(0,maxv);
		ca=cb=cc=cd=0;
		p=fac[i];
		while(!(a%p))a/=p,++ca;
		while(!(b%p))b/=p,++cb;
		while(!(c%p))c/=p,++cc;
		while(!(d%p))d/=p,++cd;
		if(ca==cb)range&=Range(ca,maxv);
		else if(ca>cb)range&=Range(cb,cb);
		else return 0;
		if(cc==cd)range&=Range(0,cc);
		else if(cc<cd)range&=Range(cd,cd);
		else return 0;
		if(range.r<range.l)return 0;
		ans*=range.r-range.l+1;
	}
	return ans;
}
int main(){
	calcPrime();
    int n=read();
    for(int i=0;i<n;++i)
        printf("%d\n",foo());
    return 0;
}

