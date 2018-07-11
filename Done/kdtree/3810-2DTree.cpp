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
const int size=100005,inf=200005;
struct Pos3{
	int x,y,z;
} P[size];
std::pair<int,int> idx[size];
struct Pos{
    int x,y;
    Pos(){}
    Pos(int x,int y):x(x),y(y){}
    bool operator<=(const Pos& rhs) const{
		return x<=rhs.x && y<=rhs.y;
	}
};
struct Node{
    Pos p,min,max;
    int c[2],siz,fa;
    bool active;
} T[size];
int cnt=0;
bool cmpX(const Pos3& a,const Pos3& b){
    return a.x<b.x;
}
bool cmpY(const Pos3& a,const Pos3& b){
    return a.y<b.y;
}
#define ls T[id].c[0]
#define rs T[id].c[1]
int buildTree(int b,int e,int fa=0,bool axis=false){
    if(b>=e)return 0;
    int m=(b+e)>>1;
    std::nth_element(P+b,P+m,P+e,axis?cmpX:cmpY);
    int id=++cnt;
    idx[m]=std::make_pair(P[m].z,id);
    T[id].siz=0;
    T[id].active=false;
    T[id].fa=fa;
    T[id].p=Pos(P[m].x,P[m].y);
    T[id].max=Pos(-1,-1);
	T[id].min=Pos(inf,inf);
    ls=buildTree(b,m,id,!axis);
    rs=buildTree(m+1,e,id,!axis);
    return id;
}
void updateMin(Pos& a,const Pos& b){
    a.x=std::min(a.x,b.x);
    a.y=std::min(a.y,b.y);
}
void updateMax(Pos& a,const Pos& b){
    a.x=std::max(a.x,b.x);
    a.y=std::max(a.y,b.y);
}
void makeActive(int id){
	T[id].active=true;
	Pos p=T[id].p;
	while(id){
		++T[id].siz;
		updateMin(T[id].min,p);
        updateMax(T[id].max,p);
		id=T[id].fa;
	}
}
int ans[size]={};
Pos p;
int res;
void query(int id){
	if(T[id].siz==0)return;
	if(T[id].max<=p)res+=T[id].siz;
	else if(T[id].min<=p){
		if(T[id].active && T[id].p<=p)++res;
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
    std::sort(idx,idx+n);
    int cur=0;
	for(int z=0;z<=k && cur<n;++z){
		int beg=cur;
		while(cur<n && idx[cur].first==z){
			makeActive(idx[cur].second);
			++cur;
		}
		for(int i=beg;i<cur;++i){
			res=0;
			p=T[idx[i].second].p;
			query(rt);
			++ans[res];
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
    return 0;
}

