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
int A[5000010],S[5000010]={};
int main(){
	int n,p;
	n=read();
	p=read();
	for(int i=1;i<=n;++i)A[i]=read();
	int l,r,w;
	for(int i=0;i<p;++i){
		l=read();
		r=read();
		w=read();
		S[l]+=w;
		S[r+1]-=w;
	}
	for(int i=1;i<=n;++i)S[i]+=S[i-1];
	int minv=1<<30;
	for(int i=1;i<=n;++i){
		int v=A[i]+S[i];
		if(v<minv)minv=v;
	}
	printf("%d\n",minv);
	return 0;
}

