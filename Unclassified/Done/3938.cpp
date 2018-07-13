#include <cstdio>
#include <algorithm>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar('\n');
}
long long fib[61];
int main(){
	int m=read();
	fib[1]=fib[2]=1;
	for(int i=3;i<=60;++i)
		fib[i]=fib[i-1]+fib[i-2];
	long long a,b;
	for(int i=0;i<m;++i){
		a=read();
		b=read();
		while(a!=b){
			int pa=std::lower_bound(fib+1,fib+61,a)-fib-1;
			int pb=std::lower_bound(fib+1,fib+61,b)-fib-1;
			if(a>b)a-=fib[pa];
			else b-=fib[pb];
		}
		print(a);
	}	
	return 0;
}

