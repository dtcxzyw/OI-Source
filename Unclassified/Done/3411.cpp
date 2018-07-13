#include <cstdio>
#include <algorithm>
#include <cstring>
const int size=1000001;
int A[size],F[size],L[size];
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
bool test(int l,int r){
	for(int i=A[l]+1;i<A[r];++i)
		if(F[i]<size && (F[i]<l || r<L[i]))
			return false;
	return true;
}
int main(){
	int n=read();
	memset(F,0x3f,sizeof(F));
	memset(L,0,sizeof(L));
	for(int i=0;i<n;++i){
		int k=read();
		A[i]=k;
		F[k]=std::min(F[k],i);
		L[k]=std::max(L[k],i);
	}
	int ans=0;
	for(int i=0;i<n;++i)
		for(int j=i+ans+1;j<n;++j)
			if(test(i,j))
				ans=j-i;
	printf("%d\n",n-ans);
	return 0;
}

