#include <cstdio>
#include <algorithm>
long long ans=0;
bool encode=false;
int decode(int x){ 
	return x^(ans&0x7fffffff);
}
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
	int val=flag?-res:res;
	return encode?decode(val):val;
}
int getOp(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c;
}
const int size=400100;
struct Vec2{
	int x,y;
	Vec2(){}
	Vec2(int px,int py):x(px),y(py){}
	Vec2 operator+(Vec2 rhs) const{
		return Vec2(x+rhs.x,y+rhs.y);
	}
	Vec2 operator-(Vec2 rhs) const{
		return Vec2(x-rhs.x,y-rhs.y);
	}
	bool operator<(Vec2 rhs) const{
		return x!=rhs.x?x<rhs.x:y<rhs.y;
	}
} P[size],Pool[size*100];
int poolCur=0;
long long dot(Vec2 a,Vec2 b){
	return static_cast<long long>(a.x)*b.x+static_cast<long long>(a.y)*b.y;
}
long long cross(Vec2 a,Vec2 b){
	return static_cast<long long>(a.x)*b.y-static_cast<long long>(b.x)*a.y;
}
long long side(Vec2 base,Vec2 a,Vec2 b){
	return cross(a-base,b-base);
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
struct Array{
	Vec2* array;
	int siz;
	void init(){
		siz=0;
		array=Pool+poolCur;
	}
};
struct Seg{
	Array top,bottom;
} seg[size<<2];
int p=0;
void addPoint(int l,int r,int id){
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)addPoint(ls);
		else addPoint(rs);
	}
	if(r==p){
		std::sort(P+l,P+r+1);
		Array& top=seg[id].top;
		top.init();
		for(int i=l;i<=r;++i){
			while(top.siz>1 && side(top.array[top.siz-2],top.array[top.siz-1],P[i])>=0)--top.siz;
			top.array[top.siz++]=P[i];
		}
		poolCur+=top.siz;
		Array& bottom=seg[id].bottom;
		bottom.init();
		for(int i=l;i<=r;++i){
			while(bottom.siz>1 && side(bottom.array[bottom.siz-2],bottom.array[bottom.siz-1],P[i])<=0)--bottom.siz;
			bottom.array[bottom.siz++]=P[i];
		}
		poolCur+=bottom.siz;
	}
}
long long maxv(long long a,long long b){
	return a>b?a:b;
}
Vec2 qv;
long long queryFull(int id){
	Array& array=(qv.y>0?seg[id].top:seg[id].bottom);
	int l=0,r=array.siz-1;
	while(r-l>=3){
		int lm=((l<<1)+r)/3;
		int rm=(l+(r<<1))/3;
		if(dot(array.array[lm],qv)<dot(array.array[rm],qv))l=lm;
		else r=rm;
	}
	long long ans=-1LL<<60;
	for(int i=l;i<=r;++i)ans=maxv(ans,dot(array.array[i],qv));
	return ans;
}
int nl,nr;
long long query(int l,int r,int id){
	if(nl<=l && r<=nr)return queryFull(id);
	else{
		int m=(l+r)>>1;
		long long res=-1LL<<60;
		if(nl<=m)res=maxv(res,query(ls));
		if(m<nr)res=maxv(res,query(rs));
		return res;
	}
}
int main(){
	int n=read();
	encode=getOp()!='E';
	for(int i=0;i<n;++i)
		if(getOp()=='A'){
			int x=read();
			int y=read();
			P[++p]=Vec2(x,y);
			addPoint(1,n,1);
		}
		else{
			int x=read();
			int y=read();
			qv=Vec2(x,y);
			nl=read();
			nr=read();
			ans=query(1,n,1);
			printf("%lld\n",ans);
		}
	return 0;
}

