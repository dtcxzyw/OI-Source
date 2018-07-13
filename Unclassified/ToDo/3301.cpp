#include <cstdio>
typedef unsigned int uint;
uint read(){
	uint res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
uint p;
uint foo(){
	uint n=read();
	uint n1=read();
	uint n2=read();
	uint m=read();
	
}
int main(){
	uint t=read();
	p=read();
	while(t--)printf("%u\n",foo());
	return 0;
}

