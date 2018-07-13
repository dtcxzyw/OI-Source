#include <cstdio>
long long con[15]={};
void pre(){
	con[1]=1;
	for(int i=2;i<15;++i)
		con[i]=con[i-1]*10;
	for(int i=1;i<15;++i)
	    con[i]*=i;
}
void calc(long long x,long long base,long long* res){
	if(x>=10)calc(x/10,base,res);
	res[x%10]+=base;	
}
void foo(long long x,long long* res){
	if(x<10){
        for(int i=1;i<=x;++i)
            ++res[i];
        return;
	}
	
	long long base,sh;
	for(base=1,sh=0;base<=x;base*=10,++sh);
	for(;base>=10;base/=10,--sh){
		long long prev=x/base,now=x/(base/10)-prev*10;
		if(prev)calc(prev,now*base/10,res);
		
		for(int i=0;i<10;++i)
			res[i]+=con[sh-1]*now;
		
		for(int i=(prev==0);i<now;++i)
		    res[i]+=base/10;
		    
	    if(prev==0){
	        long long sub;
	        for(sub=base/100;sub>=1;sub/=10)
	            res[0]-=sub;
	    }
	}
	calc(x,1,res);
}
long long cnt[2][10]={};
int main(){
	pre();
	long long a,b;
	scanf("%lld%lld",&a,&b);
	foo(a-1,cnt[0]);
	foo(b,cnt[1]);
	for(int i=0;i<10;++i)
		printf("%lld ",cnt[1][i]-cnt[0][i]);
	return 0;
}

