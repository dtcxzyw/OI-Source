#include <cstdio>
const int size=2000000;
int v[size],q[size];
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,m;
	n=read();
	m=read();
	for(int i=0;i<n;++i)
		v[i]=read();
	int b=0,e=1;
	puts("0");
	q[b]=0;
	for(int i=1;i<n;++i){
		if(i>1){
			while(b<e && v[i-1]<v[q[e-1]])--e;
			q[e++]=i-1;
		}
		while(b<e && q[b]<i-m)++b;
		printf("%d\n",v[q[b]]);
	}
	return 0;
}

