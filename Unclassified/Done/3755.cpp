#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100005;
struct Seg{
	int l,r;
	long long sum;
} T[size*20];
int root[size]={},icnt=0;
int pos,val;
int insert(int l,int r,int src){
	int id=++icnt;
	T[id]=T[src];
	T[id].sum+=val;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)T[id].l=insert(l,m,T[id].l);
		else T[id].r=insert(m+1,r,T[id].r);
	}
	return id;
}
int nl,nr;
long long res;
void query(int l,int r,int a,int b){
	if(nl<=l && r<=nr)res+=T[a].sum-T[b].sum;
	else{
		int m=(l+r)>>1;
		if(nl<=m)query(l,m,T[a].l,T[b].l);
		if(m<nr)query(m+1,r,T[a].r,T[b].r);
	}
}
struct Info{
	int x,y,p;
	bool operator<(const Info& rhs) const{
		return x<rhs.x;
	}
} P[size];
int X[size],Y[size];
int findL(int* P,int siz,int x){
	return std::lower_bound(P+1,P+siz+1,x)-P;
}
int findR(int* P,int siz,int x){
	return std::upper_bound(P+1,P+siz+1,x)-P;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		X[i]=P[i].x=read();
		Y[i]=P[i].y=read();
		P[i].p=read();
	}
	std::sort(X+1,X+n+1);
	int sizX=std::unique(X+1,X+n+1)-(X+1);
	std::sort(Y+1,Y+n+1);
	int sizY=std::unique(Y+1,Y+n+1)-(Y+1);
	std::sort(P+1,P+n+1);
	for(int i=1,l=1;i<=sizX;++i){
		root[i]=root[i-1];
		while(l<=n && P[l].x==X[i]){
			pos=findL(Y,sizY,P[l].y);
			val=P[l].p;
			root[i]=insert(1,sizY,root[i]);
			++l;
		}
	}
	for(int i=0;i<m;++i){
		int bx=findL(X,sizX,read());
		int by=findL(Y,sizY,read());
		int ex=findR(X,sizX,read())-1;
		int ey=findR(Y,sizY,read())-1;
		res=0;
		if(bx<=ex && by<=ey){
			nl=by,nr=ey;
			query(1,sizY,root[ex],root[bx-1]);
		}
		printf("%lld\n",res);
	}
	return 0;
}

