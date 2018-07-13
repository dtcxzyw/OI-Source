#include <cstdio>
#include <algorithm>
#include <cmath>
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
int getOp(){
    int c;
    do c=getchar();
    while(c!='R'&&c!='Q');
    return c;
}
const int size=10100;
int bid[size];
struct Query{
	int t,id,l,r;
	bool operator<(const Query& rhs) const{
		if(bid[l]==bid[rhs.l]){
			if(bid[r]==bid[rhs.r])
				return t<rhs.t;
			return r<rhs.r;
		}
		return l<rhs.l;
	}
} Q[size];
struct Change{
	int p,c,lc;
} C[size];
int cnt[size*100]={},ans=0,res[size],A[size],l=1,r=0;
bool in(int p){
	return l<=p && p<=r;
}
void insert(int p){
	if(++cnt[A[p]]==1)++ans;
}
void erase(int p){
	if(--cnt[A[p]]==0)--ans;
}
void apply(int t){
	C[t].lc=A[C[t].p];
	bool flag=in(C[t].p);
	if(flag)erase(C[t].p);
	A[C[t].p]=C[t].c;
	if(flag)insert(C[t].p);
}
void undo(int t){
	bool flag=in(C[t].p);
	if(flag)erase(C[t].p);
	A[C[t].p]=C[t].lc;
	if(flag)insert(C[t].p);
}
int main(){
    int n=read();
    int m=read();
    for(int i=1;i<=n;++i)A[i]=read();
	int bsiz=sqrt(n);
    for(int i=1;i<=n;++i)bid[i]=i/bsiz;
    int qc=0,cc=0;
	for(int i=0;i<m;++i)
		if(getOp()=='R'){
			++cc;
			C[cc].p=read();
			C[cc].c=read();
		}
		else{
			Q[qc].t=cc,Q[qc].id=qc;
			Q[qc].l=read();
			Q[qc].r=read();
			++qc;
		}
	std::sort(Q,Q+qc);
	int t=0;
	for(int i=0;i<qc;++i){
		while(t<Q[i].t)apply(++t);
		while(t>Q[i].t)undo(t--);
		while(r<Q[i].r)insert(++r);
		while(r>Q[i].r)erase(r--);
		while(l<Q[i].l)erase(l++);
		while(l>Q[i].l)insert(--l);
		res[Q[i].id]=ans;
	}
	for(int i=0;i<qc;++i)
		printf("%d\n",res[i]);
	return 0;
}

