#include <cstdio>
#include <algorithm>
#include <cstring>
int read(){
    int res=0,c;
    bool flag=false;
    do{
    	c=getchar();
    	flag|=c=='-';
    }
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return flag?-res:res;
}
typedef long long Int64;
int iabs(int x){
    return x>=0?x:-x;
}
const int size=100005;
struct Pos{
    int x,y,id;
} P[size];
void updateMin(Pos& a,const Pos& b){
    a.x=std::min(a.x,b.x);
    a.y=std::min(a.y,b.y);
    a.id=std::min(a.id,b.id);
}
void updateMax(Pos& a,const Pos& b){
    a.x=std::max(a.x,b.x);
    a.y=std::max(a.y,b.y);
    //a.id=std::max(a.id,b.id);
}
struct Node{
    Pos p,min,max;
    int c[2];
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
#define ls T[id].c[0]
#define rs T[id].c[1]
int buildTree(int b,int e,bool axis=false){
    if(b>=e)return 0;
    int m=(b+e)>>1;
    std::nth_element(P+b,P+m,P+e,axis?cmpX:cmpY);
    int id=++cnt;
    T[id].max=T[id].min=T[id].p=P[m];
    ls=buildTree(b,m,!axis);
    update(id,ls);
    rs=buildTree(m+1,e,!axis);
    update(id,rs);
    return id;
}
struct Key{
    Int64 dis;
    int id;
    Key():dis(-1),id(-1){}
    bool operator<(const Key& rhs) const{
        return dis==rhs.dis?id<rhs.id:dis>rhs.dis;
    }
};
class TinyHeap{
private:
    Key A[25];
    int siz;
public:
    void reset(int k){
        siz=k;
        memset(A,-1,sizeof(Key)*siz);
    }
    const Key& top() const{
        return *A;
    }
    void tryPush(const Key& k){
        if(k<top()){
            std::pop_heap(A,A+siz);
            A[siz-1]=k;
            std::push_heap(A,A+siz);
        }
    }
} heap;
Pos p;
Key buildKey(const Pos& a){
    Key k;
    Int64 dx=p.x-a.x,dy=p.y-a.y;
    k.dis=dx*dx+dy*dy;
    k.id=a.id;
    return k;
}
Key buildKey(int id){
    Key key;
    if(id){
        Int64 dx=std::max(iabs(p.x-T[id].min.x),iabs(p.x-T[id].max.x));
        Int64 dy=std::max(iabs(p.y-T[id].min.y),iabs(p.y-T[id].max.y));
        key.dis=dx*dx+dy*dy;
        key.id=T[id].min.id;
    }
    return key;
}
void query(int id){
    heap.tryPush(buildKey(T[id].p));
    Key lk=buildKey(ls),rk=buildKey(rs);
    if(rk<lk)std::swap(lk,rk),std::swap(ls,rs);
    if(lk<heap.top())query(ls);
    if(rk<heap.top())query(rs);
}
int main(){
    int n=read();
    for(int i=0;i<n;++i){
        P[i].x=read();
        P[i].y=read();
        P[i].id=i+1;
    }
    int rt=buildTree(0,n);
    int m=read();
    for(int i=0;i<m;++i){
        p.x=read();
        p.y=read();
        int k=read();
        heap.reset(k);
        query(rt);
        printf("%d\n",heap.top().id);
    }
    return 0;
}

