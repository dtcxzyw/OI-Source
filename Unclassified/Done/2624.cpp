#include <cstdio>
class BigNum
{
private:
    static const int bit=9;
    static const unsigned long long mod=1000000000ULL;
    unsigned int mData[2021];
    int mSize;
public:
    BigNum(int i):mSize(1)
    {
        mData[0]=i;
    }
    void operator*=(long long rhs)
    {
        if(rhs==0)mSize=1,mData[0]=0;
        if(mSize==1 && mData[0]==0)return;
        unsigned long long tmp=0;
        for(int i=0;i<mSize;++i)
        {
            tmp+=mData[i]*rhs;
            mData[i]=tmp%mod;
            tmp/=mod;
        }
        if(tmp)
        {
            mData[mSize]=tmp;
            ++mSize;
        }
    }
    void print() const
    {
        printf("%d",mData[mSize-1]);
        for(int i=mSize-2;i>=0;--i)
            printf("%09d",mData[i]);
    }
};
const int size=1005,maxp=200;
int A[size],prime[maxp],fac[1001][maxp]={},c[maxp]={},pcnt=0;
void pre(int n){
	for(int i=2;i<=n;++i){
		int x=i;
		for(int j=1;j<=pcnt && x!=1;++j)
			while(x%prime[j]==0){
				x/=prime[j];
				++fac[i][j];
			}
		if(x==i)prime[++pcnt]=i,fac[i][pcnt]=1;
	}
}
void mul(int n,int k){
	for(int i=1;i<=pcnt;++i)
		c[i]+=fac[n][i]*k;
}
int main(){
	int n;
	scanf("%d",&n);
	long long cnt=0,sum=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);
		if(A[i]!=-1){
			++cnt;
			sum+=A[i]-1;
		}
	}
	if(sum>n-2)puts("0");
	else{
		pre(n);
		for(int i=2;i<=n-2;++i)mul(i,1);
		mul(n-cnt,n-2-sum);
		for(int i=n-2-sum;i>=2;--i)
			mul(i,-1);
		for(int i=1;i<=n;++i)
			if(A[i]!=-1){
				for(int j=2;j<A[i];++j)
					mul(j,-1);
			}
		BigNum res(1);
		for(int i=1;i<=pcnt;++i)
			for(int j=1;j<=c[i];++j)
				res*=prime[i];
		res.print();
	}
	return 0;
}

