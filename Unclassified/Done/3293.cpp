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
const int size=200005,maxv=100000;
struct Seg{
	int l,r,siz;
} T[size*20];
int pos,icnt=0;
void insert(int l,int r,int& id){
	T[++icnt]=T[id];
	id=icnt;
	++T[id].siz;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)insert(l,m,T[id].l);
		else insert(m+1,r,T[id].r);
	}
}
int nl,nr;
bool query(int l,int r,int a,int b){
	if(T[a].siz==T[b].siz)return false;
	if(nl<=l && r<=nr)return true;
	else{
		int m=(l+r)>>1;
		bool res=false;
		if(nl<=m)res=query(l,m,T[a].l,T[b].l);
		if(!res && m<nr)res=query(m+1,r,T[a].r,T[b].r);
		return res;
	}
}
int root[size];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		root[i]=root[i-1];
		pos=read();
		insert(0,maxv,root[i]);
	}
	for(int i=0;i<m;++i){
		int b=read();
		int x=read();
		int l=read();
		int r=read();
		int cur=0;
		for(int j=17;j>=0;--j){
			int mask=1<<j;
			int bit=(b&mask)^mask;
			nl=std::max(0,cur+bit-x);
			nr=std::min(maxv,cur+bit+mask-1-x);
			if(nl<=nr && query(0,maxv,root[r],root[l-1]))cur|=bit;
			else cur|=bit^mask;
		}
		printf("%d\n",cur^b);
	}
	return 0;
}


