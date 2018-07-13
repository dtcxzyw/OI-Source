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
const int size=20100;
int sg(int x,int y){
	long long res=0,half=1,mod=2;
	while(true){
		if(x%mod<half && y%mod<half)return res;
		half<<=1;
		mod<<=1;
		++res;
	}
}
int A[size];
bool foo(){
	int n=read()/2,ans=0;
	for(int i=1;i<=n;++i)
		ans^=sg(read()-1,read()-1);
	return ans;
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)puts(foo()?"YES":"NO");
	return 0;
}

