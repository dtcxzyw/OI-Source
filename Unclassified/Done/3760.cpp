#include <cstdio>
#include <cstring>
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
const int size=1<<22;
int A[100100],S[size];
void add(int x){
	++x;
	while(x<=size){
		S[x]^=1;
		x+=x&-x;
	}
}
int query(int x){
	++x;
	int res=0;
	while(x){
		res^=S[x];
		x-=x&-x;
	}
	return res;
}
int main(){
	int n=read();
	A[0]=0;
	for(int i=1;i<=n;++i)
		A[i]=A[i-1]+read();
	int res=0;
	for(int k=0;k<=20;++k){
		int cnt=0;
		memset(S,0,sizeof(S));
		add(0);
		int bit=1<<k,mask=(1<<(k+1))-1;
		for(int i=1;i<=n;++i){
			int nxt=A[i]&mask;
			if(nxt&bit)cnt^=query(nxt^bit)^query(mask)^query(nxt);
			else cnt^=query(nxt^bit)^query(nxt);
			add(nxt);
		}
		if(cnt)res+=bit;
	}
	printf("%d\n",res);		
	return 0;
}

