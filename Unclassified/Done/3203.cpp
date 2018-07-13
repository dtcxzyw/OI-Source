#include <cstdio>
#include <cmath>
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
const int size=200005;
int nxt[size],t[size];
int query(int u){
	int res=0;
	while(~u){
		res+=t[u];
		u=nxt[u];
	}
	return res;
}
int bend[size];
void modify(int u,int k,int n){
	int pos=u+k;
	if(pos<bend[u]){
		t[u]=t[pos]+1;
		nxt[u]=nxt[pos];
	}
	else if(pos<n){
		t[u]=1;
		nxt[u]=pos;
	}
	else{
		t[u]=1;
		nxt[u]=-1;	
	}
}
int A[size];
int main(){
	int n=read();
	int bsiz=sqrt(n)+1;
	for(int i=0;i<n;++i)A[i]=read();
	for(int i=0;i<n;++i)bend[i]=std::min(n,(i/bsiz+1)*bsiz);
	
	for(int i=n-1;i>=0;--i)
		modify(i,A[i],n);
	
	int m=read();
	for(int i=0;i<m;++i)
		if(read()==1)printf("%d\n",query(read()));
		else{
			int u=read();
			A[u]=read();
			for(int i=u;i>=0 && bend[i]==bend[u];--i)
				modify(i,A[i],n);
		}
	return 0;
}

