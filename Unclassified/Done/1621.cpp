#include <cstdio>
#include <vector>
int fa[100001];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool isPrime(int x){
	for(int i=2;i*i<=x;++i)
		if(x%i==0)return false;
	return true;
}
std::vector<int> prime;
int main(){
	int a,b,p;
	scanf("%d%d%d",&a,&b,&p);
	for(int i=p;i<=b;++i)
		if(isPrime(i))
			prime.push_back(i);
	for(int i=a;i<=b;++i)
		fa[i]=i;
	for(int i=0;i<prime.size();++i){
		int p=prime[i],begin=a%p?(a/p+1)*p:a,fb=find(begin);
		for(int j=begin+p;j<=b;j+=p){
			int fj=find(j);
			if(fb!=fj)
				fa[fj]=fb;
		}
	}
	int cnt=0;
	for(int i=a;i<=b;++i)
		cnt+=(find(i)==i);
	printf("%d\n",cnt);
	return 0;
}

