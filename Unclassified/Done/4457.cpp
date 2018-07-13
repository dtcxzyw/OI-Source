#include <cstdio>
#include <algorithm>
#include <cstring>
const int size=1515,mod=1000000007;
typedef long long Int64;
Int64 powm(Int64 x,int k){
    Int64 res=1;
    while(k){
        if(k&1)res=res*x%mod;
        k>>=1,x=x*x%mod;
    }
    return res;
}
Int64 inv(Int64 x){
    return powm(x,mod-2);
}
Int64 A[size][size],B[size],ans[size];
int solve(int n,int init){
    for(int i=n;i>=0;--i){
        int x=(i==0 || A[i][i])?i:i-1;
        if(A[x][i]==0)return -1;
        if(i==0)break;
        if(i!=x){
            for(int j=0;j<=i;++j)
                std::swap(A[i][j],A[x][j]);
            std::swap(B[i],B[x]);
        }
        else{
        	Int64 invv=inv(A[i][i]);
            int j=i-1;
            if(A[j][i]==0)continue;
            Int64 mul=A[j][i]*invv%mod;
            for(int k=0;k<=i;++k)
                A[j][k]=(A[j][k]-A[i][k]*mul)%mod;
            B[j]=(B[j]-B[i]*mul)%mod;
        }
    }
    for(int i=0;i<=init;++i){
    	Int64 res=B[i];
    	for(int j=0;j<i;++j)
    		res=(res-A[i][j]*ans[j])%mod;
    	ans[i]=res*inv(A[i][i])%mod;
    }
    return (ans[init]+mod)%mod;
}
Int64 LUT[size],invTable[size];
int foo(int n,int init,int m,int k){
    Int64 p=inv(m+1),ip=(1-p+mod)%mod,invip=inv(ip);
    {
    	memset(LUT,0,sizeof(LUT));
    	if(ip==0){
    		if(k<=n)LUT[k]=powm(p,k);
    	}
    	else{
            Int64 cur=powm(ip,k),c=1;
            int end=std::min(n,k);
            for(int i=0;i<=end;++i){
                LUT[i]=cur*c%mod;
                c=c*(k-i)%mod*invTable[i+1]%mod;
                cur=cur*p%mod*invip%mod;
            }
    	}
    }
    memset(A,0,sizeof(A));
    for(int i=0;i<=n;++i){
        A[i][i]=-1;
        B[i]=(i==0?0:-1);
    }
    for(int i=0;i<=n;++i){
        int begin=std::max(1,i-1),end=std::min(n,i+k);
        for(int j=begin;j<=end;++j){
        	if(j==n)A[j][i]=(A[j][i]+LUT[j-i])%mod;
            else{
                if(j>=i)A[j][i]=(A[j][i]+ip*LUT[j-i])%mod;
            	if(j+1>=i)A[j][i]=(A[j][i]+p*LUT[j+1-i])%mod;
            }
        }
    }
    return solve(n,init);
}
int main(){
    invTable[0]=invTable[1]=1;
    for(int i=2;i<size;++i)
        invTable[i]=(mod-mod/i)*invTable[mod%i]%mod;
    int t;
    scanf("%d",&t);
    while(t--){
        int n,p,m,k;
        scanf("%d%d%d%d",&n,&p,&m,&k);
        printf("%d\n",foo(n,p,m,k));
    }
    return 0;
}

