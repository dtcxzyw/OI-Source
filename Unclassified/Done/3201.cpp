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
const int size=100005;
int A[size],head[size*10]={},nxt[size],siz[size*10]={},fa[size*10];
void merge(int x,int y,int& cnt){
	if(cnt==1 || x==y)return;
	if(siz[fa[x]]>siz[fa[y]])std::swap(fa[x],fa[y]);
	x=fa[x],y=fa[y];
	if(siz[x]==0)return;
	for(int i=head[x];i;i=nxt[i]){
		if(A[i-1]==y)--cnt;
		if(A[i+1]==y)--cnt;
	}
	int nxtNode;
	for(int i=head[x];i;i=nxtNode){
		A[i]=y;
		nxtNode=nxt[i];
		nxt[i]=head[y];
		head[y]=i;
	}
	siz[y]+=siz[x];
	siz[x]=0;
}
int main(){
	int n=read();
	int m=read();
	int cnt=0;
	for(int i=1;i<=1000000;++i)fa[i]=i;
	for(int i=1;i<=n;++i){
		A[i]=read();
		if(A[i]!=A[i-1])++cnt;
		nxt[i]=head[A[i]];
		head[A[i]]=i;
		++siz[A[i]];
	}
	for(int i=0;i<m;++i){
		int op=read();
		if(op==1){
			int x=read();
			int y=read();
			merge(x,y,cnt);
		}
		else printf("%d\n",cnt);
	}
	return 0;
}

