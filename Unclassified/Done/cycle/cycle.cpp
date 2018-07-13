#include <iostream>
#include <set>
#include <map>
using namespace std;
int gcd(int a,int b){
    if(b)return gcd(b,a%b);
    return a;
}
int k;
bool test(int x,int y){
    if(y==1)return true;
    set<int> mod;
    int front=x;
    mod.insert(x);
    while(true){
        x=static_cast<long long>(x)*k%y;
        if(mod.find(x)!=mod.end())return x==front;
        if(x==0)return false;
        mod.insert(x);
    }
}
set<int> prime;
map<int,int> cache;
int findFac(int x){
	if(cache.find(x)!=cache.end())return cache[x];
	if(prime.find(x)!=prime.end())return 0;
	for(auto&& i:prime)
		if(x%i==0){
			cache[x]=i; 
			return i;
		}
	if(x!=1)prime.insert(x);
	return 0;
}
int main(){
    int n,m;
    cin>>n>>m>>k;
    int sum=0,fac;
    for(int y=1;y<=m;++y){
    	set<int> suc{0}; 
    	for(int x=1;x<=n;++x)
    		if(gcd(x,y)==1){
				if(x>y)sum+=(suc.find(x%y)!=suc.end());
				else if(fac=findFac(x)){
					if(suc.find(fac)!=suc.end())
						++sum,suc.insert(x);
				}
				else if(test(x,y))++sum,suc.insert(x);
			}
    }
	
    cout<<sum;
    return 0;
}

