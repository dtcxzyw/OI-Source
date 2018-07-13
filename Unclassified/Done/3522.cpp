#include <cstdio>
#include <algorithm>
const int maxv=1000000000,size=1000000;
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int L[size],R[size],q[size],p[size];
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		L[i]=read();
		R[i]=read();
	}
	int b=0,e=0,ans=0,last=0;
	for(int i=0;i<n;++i){
		while(e>b && L[q[e-1]]<=L[i])--e;
			q[e++]=i;
		p[i]=last;
		while(b<e && L[q[b]]>R[i])p[i]=q[b++]+1;
		last=p[i];
		ans=std::max(ans,i-p[i]+1);
	}
	printf("%d\n",ans);
	return 0;
}

