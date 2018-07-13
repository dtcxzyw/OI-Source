#include <cstdio>
#include <vector>
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
void printImpl(long long x){
    if(x>=10)printImpl(x/10);
    putchar('0'+x%10);
}
void print(long long x){
    printImpl(x);
    putchar('\n');
}
const int size=30000001;
int r[size]={},ls[size]={},rs[size]={},siz[size]={},cnt=0,msiz,pos;
void modify(int l,int r,int& id){
	if(!id)id=++cnt;	
	++siz[id];
	if(l<r){
		int m=(l+r)>>1;
		if(pos<=m)modify(l,m,ls[id]);
		else modify(m+1,r,rs[id]);
	}
}
int query(int l,int r,int id,int x){
	if(l==r)return l;
	int m=(l+r)>>1,lsiz=m-l+1-siz[ls[id]];	
	if(x<=lsiz)return query(l,m,ls[id],x);
	return query(m+1,r,rs[id],x-lsiz);
}
std::vector<long long> cache[300011];
int n,m;
long long del1(int x,long long rep){
	pos=query(1,msiz,r[n+1],x);
	modify(1,msiz,r[n+1]);
	long long res=(pos<=n?1LL*pos*m:cache[n+1][pos-n-1]);
	cache[n+1].push_back(rep?rep:res);
	return res;
}
long long del2(int x,int y){
	pos=query(1,msiz,r[x],y);
	long long res=(pos<m?1LL*(x-1)*m+pos:cache[x][pos-m]);
	modify(1,msiz,r[x]);
	cache[x].push_back(del1(x,res)); 
	return res;
}
int main(){
    n=read();
    m=read();
    int q=read();
    msiz=(n>m?n:m)+q;
    for(int i=0;i<q;++i){
        int x=read();
        int y=read();
     	if(y==m)print(del1(x,0));
    	else print(del2(x,y));
	}
    return 0;
}

