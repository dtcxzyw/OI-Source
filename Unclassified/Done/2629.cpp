#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=1000010;
int A[size],S[size],L[size],R[size];
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		S[i]=S[i-1]+A[i];
	}
	L[0]=R[n+1]=1<<30;
	for(int i=1;i<=n;++i)L[i]=std::min(S[i],L[i-1]);
	for(int i=n;i>=1;--i)R[i]=std::min(A[i],R[i+1]+A[i]);
	int ans=0;
	for(int i=1;i<=n;++i)
		if(L[i-1]+(S[n]-S[i-1])>=0&&R[i]>=0)++ans;
	printf("%d\n",ans);
	return 0;
}

