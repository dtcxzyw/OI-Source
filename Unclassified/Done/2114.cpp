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
int getOp(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c;
}
const int size=100100;
int op[size],t[size];
int apply(int x,int n){
	for(int i=1;i<=n;++i)
		switch(op[i]){
			case 'A':x&=t[i];break;
			case 'O':x|=t[i];break;
			case 'X':x^=t[i];break;
		}
	return x;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		op[i]=getOp();
		t[i]=read();
	}
	int off=apply(0,n),on=apply((1LL<<31)-1,n),ans=0;	
	for(int i=30;i>=0;--i){
		int bit=1<<i;
		if(off&bit)ans+=bit;
		else if(on&bit && m>=bit)m-=bit,ans+=bit;
	}
	printf("%d\n",ans);
	return 0;
}

