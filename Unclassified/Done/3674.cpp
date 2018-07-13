#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>
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
const int end=100100,size=end+100;
int cnt[size]={};
std::bitset<size> set,invset;
bool sum(int x){
	return (set&(invset>>(end-x))).any();
}
bool sub(int x){
	return ((set<<x)&set).any();
}
bool mul(int x){
	for(int i=1;i*i<=x;++i)
		if(x%i==0 && set[i] && set[x/i])
			return true;
	return false;
}
int A[size];
void insert(int x){
	int k=A[x];
	if(++cnt[k]==1){
		set.set(k,true); 
		invset.set(end-k,true);
	}
}
void erase(int x){
	int k=A[x];
	if(--cnt[k]==0){
		set.set(k,false); 
		invset.set(end-k,false);
	}
}
void update(int nl,int nr){
	static int l=1,r=0;
	while(r<nr)insert(++r);
	while(nr<r)erase(r--);
	while(l<nl)erase(l++);
	while(nl<l)insert(--l);
}
int block[size];
struct Query{
	int id,op,l,r,x;
	bool operator<(const Query& rhs) const{
		if(block[l]==block[rhs.l])return r<rhs.r;
		return l<rhs.l;
	}
} Q[size];
bool ans[size];
int main(){
	int n=read();
	int m=read();
	int bsiz=sqrt(n)+1;
	for(int i=1;i<=n;++i)block[i]=i/bsiz;
	int maxv=0;
	for(int i=1;i<=n;++i){
		A[i]=read();
		maxv=std::max(maxv,A[i]);		
	}
	for(int i=0;i<m;++i){
		Q[i].id=i;
		Q[i].op=read();
		Q[i].l=read();
		Q[i].r=read();
		Q[i].x=read();
	}
	std::sort(Q,Q+m);
	for(int i=0;i<m;++i){
		update(Q[i].l,Q[i].r);
		bool res;
		switch(Q[i].op){
			case 1:res=sub(Q[i].x);break;
			case 2:res=sum(Q[i].x);break;
			case 3:res=mul(Q[i].x);break;
		}
		ans[Q[i].id]=res;
	}
	for(int i=0;i<m;++i)
		puts(ans[i]?"hana":"bi");
	return 0;
}

