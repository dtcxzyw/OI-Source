#include <cstdio>
#include <vector>
#include <cmath>
int prime[50001],cnt=1;
bool isPrime(int x){
    for(int i=2;i*i<=x;++i)
        if(x%i==0)return false;
    return true;
}
void pre(){
    prime[0]=2;
    for(int i=3;i<50000;++i)
        if(isPrime(i))prime[cnt++]=i;
}
int ans[100000],num=1;
void mul(int a,int k){
    for(int i=0;i<k;++i){
        for(int j=1;j<=num;++j)
            ans[j]*=a;
        for(int j=1;j<=num;++j){
            ans[j+1]+=ans[j]/10;
            ans[j]%=10;
        }
        while(ans[num+1]){
            ++num;
            ans[num+1]+=ans[num]/10;
            ans[num]%=10;
        }
    }
}
int main(){
    pre();
    int n;
    scanf("%d",&n);
    std::vector<int> k;
    for(int i=0;i<=cnt && n!=1;++i)
        while(n%prime[i]==0){
            n/=prime[i];
            k.push_back(prime[i]); 
        }
    bool flag;
    do{
    	flag=false;
	    for(int i=k.size()-1;i>=0;--i){
	    	for(int j=0;j<i;++j){
	    		if(powl(prime[k.size()-i-1],k[i]*k[j]-k[i])<powl(prime[k.size()-j-1],k[j]-1)-0.1l){
	    			k[i]*=k[j];
	    			k.erase(k.begin()+j); 
					flag=true;
	    			break;
	    		}
	    	}
	    	if(flag)break;
		}
    }while(flag);
    ans[1]=1;
    for(int i=0;i<k.size();++i)
        mul(prime[k.size()-i-1],k[i]-1);
    for(int i=num;i>0;--i)
        putchar('0'+ans[i]);
    return 0;
}

