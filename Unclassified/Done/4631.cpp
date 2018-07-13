#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
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
const int size=300005;
struct Circle{
    int id,x,y,r;
    bool operator<(const Circle& rhs) const{
        return r==rhs.r?id<rhs.id:r>rhs.r;
    }
    bool intersect(const Circle& c) const{
        long long dx=x-c.x,dy=y-c.y,sr=r+c.r;
        return dx*dx+dy*dy<=sr*sr;	
    }
} C[size],A[size];
struct Node{
    int l,r,bx,ex,by,ey,id;
    void init(const Circle& c){
        bx=c.x-c.r,ex=c.x+c.r;
        by=c.y-c.r,ey=c.y+c.r;
        l=r=0;
        id=c.id;
    }
    void update(const Node& c){
        bx=std::min(bx,c.bx);
        ex=std::max(ex,c.ex);
        by=std::min(by,c.by);
        ey=std::max(ey,c.ey);
    }
    bool intersect(const Node& c) const{
        return c.ex>=bx && c.bx<=ex && c.ey>=by && c.by<=ey;  
    }
} T[size];
bool cmpX(const Circle& a,const Circle& b){
    return a.x<b.x;
}
bool cmpY(const Circle& a,const Circle& b){
    return a.y<b.y;
}
int icnt=0;
int buildTree(int l,int r){
    int mid=(l+r)>>1;
    std::nth_element(A+l,A+mid,A+r+1,rand()&1?cmpX:cmpY);
    int id=++icnt;
    T[id].init(A[mid]);
    if(l<mid){
        T[id].l=buildTree(l,mid-1);
        T[id].update(T[T[id].l]);
    }
    if(mid<r){
        T[id].r=buildTree(mid+1,r);
        T[id].update(T[T[id].r]);
    }
    return id;
}
int ans[size]={};
void erase(const Circle& c,const Node& aabb,int u){
    if(!ans[T[u].id] && c.intersect(C[T[u].id]))ans[T[u].id]=c.id;
    if(T[u].l && T[T[u].l].intersect(aabb))erase(c,aabb,T[u].l);
    if(T[u].r && T[T[u].r].intersect(aabb))erase(c,aabb,T[u].r);
}
int main(){
    srand(19260817);
    int n=read();
    for(int i=1;i<=n;++i){
        C[i].id=i;
        C[i].x=read();
        C[i].y=read();
        C[i].r=read();
    }
    memcpy(A,C,sizeof(C));
    int root=buildTree(1,n);
    std::sort(A+1,A+n+1);
    Node aabb;
    for(int i=1;i<=n;++i)
        if(!ans[A[i].id]){
            aabb.init(A[i]);
            erase(A[i],aabb,root);
        }
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    return 0;
}

