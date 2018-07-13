#include <cstdio>
#include <cmath>
#include <map>
int powm(int a,int k,int mod){
	int res=1;
	while(k){
		if(k&1)res=1LL*res*a%mod;
		k>>=1,a=1LL*a*a%mod;
	}
	return res;
}
void foo1(int a,int k,int mod){
	printf("%d\n",powm(a,k,mod));
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
void noAnswer(){
	puts("Orz, I cannot find x!");
}
void foo2(int a,int b,int p){
	int d,x,y;
	if(b%gcd(a,p)==0){
		int res=1LL*(b%p)*powm(a,p-2,p)%p;
		printf("%d\n",res);
	}
	else noAnswer();
}
void foo3(int a,int b,int p){
	if(a%p==0){
		noAnswer();
		return;
	}
	int m=ceil(sqrt(p));
	std::map<int,int> table;
	int now=b%p;
	for(int j=0;j<=m;++j){
		table[now]=j;
		now=1LL*now*a%p;
	}
	int base=powm(a,m,p);
	now=1;
	for(int i=1;i<=m;++i){
		now=1LL*now*base%p;
		std::map<int,int>::iterator it=table.find(now);
		if(it!=table.end()){
			 printf("%d\n",i*m-it->second);
			 return;
		}
	}
	noAnswer();
}
typedef void(*Func)(int,int,int);
int main(){
	int t,l;
	scanf("%d%d",&t,&l);
	Func func;
	if(l==1)func=foo1;
	else if(l==2)func=foo2;
	else func=foo3;
	int y,z,p;
	for(int i=1;i<=t;++i){
		scanf("%d%d%d",&y,&z,&p);
		func(y,z,p);
	}
	return 0;
}

