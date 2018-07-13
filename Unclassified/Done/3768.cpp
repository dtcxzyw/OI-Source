#include <cstdio>
#include <map>
typedef long long Int64;
Int64 powm(Int64 a,Int64 k,Int64 p){
    Int64 res=1;
    while(k){
        if(k&1)res=res*a%p;
        k>>=1,a=a*a%p;
    }
    return res;
}
Int64 inv6,p;
Int64 sum2(Int64 x){
	x%=p;
	return x*(x+1)%p*(x<<1|1)%p*inv6%p;
}
Int64 sum3(Int64 x){
	x%=p;
	Int64 sum1=((x*(x+1))>>1)%p;
	return sum1*sum1%p;
}
const Int64 size=6000100;
Int64 prime[size],phi[size],sum[size],siz;
bool flag[size]={};
void pre(){
	phi[1]=1;
	Int64 pcnt=0;
	for(Int64 i=2;i<=siz;++i){
		if(!flag[i]){
			prime[++pcnt]=i;
			phi[i]=i-1;
		}
		for(Int64 j=1;j<=pcnt;++j){
			Int64 val=i*prime[j];
			if(val>siz)break;
			flag[val]=true;
			if(i%prime[j])phi[val]=phi[i]*(prime[j]-1);
			else{
			    phi[val]=phi[i]*prime[j];
			    break;
			}
		}
	}	
	for(Int64 i=1;i<=siz;++i)
		sum[i]=(sum[i-1]+i*i%p*phi[i]%p)%p;
}
std::map<Int64,Int64> cache;
Int64 calcSum(Int64 n){
	if(n<=siz)return sum[n];
	Int64& val=cache[n];
	if(val)return val;
	val=sum3(n);
	Int64 pos;
	for(Int64 i=2;i<=n;i=pos+1){
		pos=n/(n/i);
		val=(val-(sum2(pos)-sum2(i-1)+p)%p*calcSum(n/i)%p)%p;
	}
	val=(val+p)%p;
	return val;
}
int main(){
	Int64 n;
	scanf("%lld%lld",&p,&n);
	siz=std::min(size-100,n);
	pre();
	inv6=powm(6,p-2,p);
	Int64 ans=0,pos;
	for(Int64 i=1;i<=n;i=pos+1){
		pos=n/(n/i);
		ans=(ans+(calcSum(pos)-calcSum(i-1)+p)%p*sum3(n/i)%p)%p;
	}
	ans=(ans+p)%p;
	printf("%lld\n",ans); 
	return 0;
}

