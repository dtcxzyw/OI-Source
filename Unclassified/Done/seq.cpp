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
const int size=1000001;
int begin[size]={},last[size]={},next[size]={},now[size],A[size];
bool foo(int n){
	int siz=read();
	for(int i=1;i<=siz;++i)A[i]=read();
	if(siz>n)return false;
	int pos=0;
	memcpy(now,begin,sizeof(now));
	for(int i=1;i<=siz;++i){
		if(now[A[i]]>pos){
			pos=now[A[i]];
			now[A[i]]=next[now[A[i]]];
		}
		else return false;
	}
	return true;
}
int main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	int n=read();
	for(int i=1;i<=n;++i){
		int x=read();
		if(last[x])next[last[x]]=i;
		else begin[x]=i;
		last[x]=i;
	}
	int m=read();
	for(int i=0;i<m;++i)puts(foo(n)?"Yes":"No");
	return 0;
}

