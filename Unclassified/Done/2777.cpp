#include <cstdio>
#include <algorithm>
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
int A[300001];
int main(){
	int n=read();
	for(int i=0;i<n;++i)
		A[i]=read();
	std::sort(A,A+n);
	int minv=0,ans=0;
	for(int i=n-1;i>=0;--i){
		if(A[i]+n>=minv)++ans;
		else break;
		minv=std::max(minv,A[i]+(n-i));
	}
	printf("%d\n",ans);
	return 0;
}

