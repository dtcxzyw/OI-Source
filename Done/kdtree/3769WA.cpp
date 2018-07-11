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
const int size=50005,inf=1<<30;
struct Pos4{
	int x,y,z,w;
} P[size];
std::pair<int,int> idx[size];
struct Pos{
    int x,y,z;
    Pos(){}
    Pos(int x,int y,int z):x(x),y(y){}
    bool operator<=(const Pos& rhs) const{
		return x<=rhs.x && y<=rhs.y && z<=rhs.z;
	}
	bool operator!=(const Pos& rhs) const{
		return x!=rhs.x || y!=rhs.y || z!=rhs.z;
	}
};
struct Node{
    Pos p,min;
    int c[2],siz,fa,mdis;
    bool active;
} T[size];
int cnt=0;
bool cmpX(const Pos4& a,const Pos4& b){
    return a.x<b.x;
}
bool cmpY(const Pos4& a,const Pos4& b){
    return a.y<b.y;
}
bool cmpZ(const Pos4& a,const Pos4& b){
    return a.z<b.z;
}
typedef bool (*Func)(const Pos4& a,const Pos4& b);
Func func[3]={cmpX,cmpY,cmpZ};
const int nxt[3]={1,2,0};
#define ls T[id].c[0]
#define rs T[id].c[1]
int buildTree(int b,int e,int fa=0,int axis=0){
    if(b>=e)return 0;
    int m=(b+e)>>1;
    std::nth_element(P+b,P+m,P+e,func[axis]);
    int id=++cnt;
    idx[m]=std::make_pair(P[m].w,id);
    T[id].siz=0;
    T[id].active=false;
    T[id].fa=fa;
    T[id].mdis=-1;
    T[id].p=Pos(P[m].x,P[m].y,P[m].z);
    //T[id].max=Pos(-1,-1,-1);
	T[id].min=Pos(inf,inf,inf);
    ls=buildTree(b,m,id,nxt[axis]);
    rs=buildTree(m+1,e,id,nxt[axis]);
    return id;
}
void updateMin(Pos& a,const Pos& b){
    a.x=std::min(a.x,b.x);
    a.y=std::min(a.y,b.y);
    a.z=std::min(a.z,b.z);
}
void makeActive(int id){
	T[id].active=true;
	Pos p=T[id].p;
	while(id){
		++T[id].siz;
		updateMin(T[id].min,p);
		id=T[id].fa;
	}
}
int getDis(int id);
int query(int id,const Pos& p,int rt){
	if(T[id].siz && T[id].min<=p){
		int res=0;
		if(id!=rt && T[id].active && T[id].p<=p)res=std::max(res,getDis(id));
		if(ls)res=std::max(res,query(ls,p,rt));
		if(rs)res=std::max(res,query(rs,p,rt));
		return res;
	}
	return 0;
}
int rt;
int getDis(int id){
	if(T[id].mdis!=-1)return T[id].mdis;
	return T[id].mdis=1+query(rt,T[id].p,id);
}
int main(){
    int n=read();
    for(int i=0;i<n;++i){
        P[i].x=read();
        P[i].y=read();
        P[i].z=read();
        P[i].w=read();
    }
    rt=buildTree(0,n);
    std::sort(idx,idx+n);
    int cur=0,ans=0;
	while(cur<n){
		int beg=cur,w=idx[cur].first;
		while(cur<n && idx[cur].first==w){
			makeActive(idx[cur].second);
			++cur;
		}
		for(int i=beg;i<cur;++i)
			ans=std::max(ans,getDis(idx[i].second));
	}
	printf("%d\n",ans);
    return 0;
}

