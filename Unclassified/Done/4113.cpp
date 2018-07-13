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
const int size=2001000;
int A[size]={},n;
void add(int x,int op){
	while(x<=n){
		A[x]+=op;
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=A[x];
		x-=x&-x;
	}
	return res;
}
struct Query{
	int l,r,id;
	bool operator<(const Query& rhs) const{
		return l<rhs.l;
	}
} q[size];
int res[size],nxt[size],cur[size]={},col[size];
int main(){
	n=read();
	int c=read();
	int m=read();
	for(int i=1;i<=n;++i)
		col[i]=read();
	for(int i=n;i>=1;--i){
		nxt[i]=cur[col[i]];
		cur[col[i]]=i;
	}
	for(int i=c;i>=1;--i)
		if(nxt[cur[i]])
			add(nxt[cur[i]],1);
	for(int i=0;i<m;++i){
		q[i].id=i;
		q[i].l=read();
		q[i].r=read();
	}
	std::sort(q,q+m);
	for(int i=0,l=1;i<m;++i){
		while(l<q[i].l){
			if(nxt[l]){
				add(nxt[l],-1);
				int n2=nxt[nxt[l]];
				if(n2)add(n2,1);
			}
			++l;
		}
		res[q[i].id]=(query(q[i].r)-query(q[i].l-1));
	}
	for(int i=0;i<m;++i)
		printf("%d\n",res[i]);
	return 0;
}

