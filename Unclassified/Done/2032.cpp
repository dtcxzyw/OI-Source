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
int A[2000001],q[2000000],b=0,e=0;
int main(){
	int n,k;
	n=read();k=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		while(b!=e && A[q[e-1]]<A[i])--e;
		q[e++]=i;
		if(i>=k){
			while(i-q[b]>=k)++b;
			printf("%d\n",A[q[b]]);
		}
	}
	return 0;	
}

