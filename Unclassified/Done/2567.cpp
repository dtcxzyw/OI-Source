#include <cstdio>
#include <vector>
long long toNum(int l,int v){
	long long res=0;
	for(int i=l-1;i>=0;--i)
		if(v&(1<<i))res=res*10+8;
		else res=res*10+6;
	return res;
}
long long obj,res;
std::vector<long long> x,y;
long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}
void DFS(int i,long long lm,bool fac){
	if(lm<=obj){
	    for(;i>=0;--i)DFS(i-1,lm/gcd(lm,y[i])*y[i],!fac);
        if(lm>1){
            if(fac)res+=obj/lm;
            else res-=obj/lm;
        }
	}
}
long long query(long long r){
    obj=r;
    y.clear();
    res=0;
    for(int i=0;i<x.size();++i)
        if(x[i]<=r/2)y.push_back(x[i]);
        else if(x[i]<=r)++res;
    DFS(y.size()-1,1,false);
    return res; 
}
int main(){
	long long a,b;
	scanf("%lld%lld",&a,&b);
	x.reserve(3000); 
	for(int i=1,base=2;;++i,base<<=1)
		for(int j=0;j<base;++j){
			long long num=toNum(i,j);
			if(num>b)goto out;
			x.push_back(num);
		}
	out:
	for(int i=0;i<x.size();++i)
		for(int j=i+1;j<x.size();++j)
			if(x[j]%x[i]==0){
				x.erase(x.begin()+j);
				--j; 
			}
	printf("%lld\n",query(b)-query(a-1));
	return 0;
}
 
