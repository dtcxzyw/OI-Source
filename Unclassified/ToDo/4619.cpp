#include <cstdio>
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
int minv(int a,int b){
    return a<b?a:b;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size=100100,mod=1000000007;
int prime[size],pcnt=0,mu[size],e[size];
long long d[size];
bool flag[size]={};
void pre(int n){
    mu[1]=1,d[1]=1;
    for(int i=2;i<=n;++i){
        if(!flag[i]){
        	prime[++pcnt]=i;
			mu[i]=-1;
			d[i]=2;
			e[i]=1;
    	}
		for(int j=1;j<=pcnt && i*prime[j]<=n;++j){
			int val=i*prime[j];
            flag[val]=true;
            if(i%prime[j]){
            	mu[val]=-mu[i];
				e[val]=1;
				d[val]=d[i]<<1;
        	}
            else{
                mu[i*prime[j]]=0;
                e[val]=e[i]+1;
                d[val]=d[i]/(e[i]+1)*(e[i]+2);
                break;
            }
        }
    }
    for(int i=1;i<=n;++i){
        mu[i]+=mu[i-1];
    	//d[i]+=d[i-1];
	}
}
Int64 foo(int n,int m){
    int x=minv(n,m);
    Int64 res=0;
    for(int i=1;i<=x;){
        int j=minv(n/(n/i),m/(m/i));
        res+=(mu[j]-mu[i-1])*d[n/i]*d[m/i];
    	i=j+1;
	}
	printf("%I64d\n",res);
    return res;
}
int main(){
    pre(100000);
    int t=read();
    while(t--){
    	int a=read();
    	int b=read();
    	int c=read();
    	int val=foo(a,b)%mod*foo(b,c)%mod*foo(a,c)%mod;
    	printf("%d\n",val);
    }
    return 0;
}

