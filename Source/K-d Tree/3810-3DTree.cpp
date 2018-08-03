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
struct Pos{
    int x,y,z;
    bool operator<=(const Pos& rhs) const{
		return x<=rhs.x && y<=rhs.y && z<=rhs.z;
	}
} P[size];
void updateMin(Pos& a,const Pos& b){
    a.x=std::min(a.x,b.x);
    a.y=std::min(a.y,b.y);
    a.z=std::min(a.z,b.z);
}
void updateMax(Pos& a,const Pos& b){
    a.x=std::max(a.x,b.x);
    a.y=std::max(a.y,b.y);
    a.z=std::max(a.z,b.z);
}
struct Node{
    Pos p,min,max;
    int c[2],siz;
} T[size];
void update(int a,int b){
    if(b){
        updateMin(T[a].min,T[b].min);
        updateMax(T[a].max,T[b].max);
    }
}
int cnt=0;
bool cmpX(const Pos& a,const Pos& b){
    return a.x<b.x;
}
bool cmpY(const Pos& a,const Pos& b){
    return a.y<b.y;
}
bool cmpZ(const Pos& a,const Pos& b){
    return a.z<b.z;
}
typedef bool (*Func)(const Pos& a,const Pos& b);
const Func func[3]={cmpX,cmpY,cmpZ};
const int nxt[3]={1,2,0};
#define ls T[id].c[0]
#define rs T[id].c[1]
int buildTree(int b,int e,int axis=0){
    if(b>=e)return 0;
    int m=(b+e)>>1;
    std::nth_element(P+b,P+m,P+e,func[axis]);
    int id=++cnt;
    T[id].siz=e-b;
    T[id].max=T[id].min=T[id].p=P[m];
    ls=buildTree(b,m,nxt[axis]);
    update(id,ls);
    rs=buildTree(m+1,e,nxt[axis]);
    update(id,rs);
    return id;
}
int ans[size]={};
Pos p;
int cur;
void query(int id){
	if(T[id].max<=p)cur+=T[id].siz;
	else if(T[id].min<=p){
		if(T[id].p<=p)++cur;
		if(ls)query(ls);
		if(rs)query(rs);
	}
}
int main(){
    int n=read();
    int k=read();
    for(int i=0;i<n;++i){
        P[i].x=read();
        P[i].y=read();
        P[i].z=read();
    }
    int rt=buildTree(0,n);
	for(int i=0;i<n;++i){
		cur=0;
		p=P[i];
		query(rt);
		++ans[cur];
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
    return 0;
}

