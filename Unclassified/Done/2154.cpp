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
int fix(int x){
    if(x>=0)return x;
    return x+(1LL<<31);
}
const int size=100100;
int C[size][11];
void pre(int n,int k){
    C[0][0]=1;
    for(int i=1;i<=n;++i){
        C[i][0]=1;
        for(int j=1;j<=k;++j)
            C[i][j]=C[i-1][j]+C[i-1][j-1];	
    }
}
struct Point{
    int x,y;
} P[size];
bool cmpY(Point lhs,Point rhs){
    return lhs.y==rhs.y?lhs.x<rhs.x:lhs.y<rhs.y;
}
int X[size],Y[size],Xc[size]={},Yc[size]={},Xcnt[size]={},A[size]={};
int find(int* b,int* e,int x){
    return std::lower_bound(b,e,x)-b+1;
}
void add(int x,int siz,int add){
    while(x<=siz){
        A[x]+=add;
        x+=x&-x;
    }
}
int query(int x){
    int res=0;
    while(x){
        res+=A[x];
        x-=x&-x;
    }
    return res;
}
int main(){
    int n=read();
    int m=read();
    int w=read();
    for(int i=0;i<w;++i){
        X[i]=P[i].x=read();
        Y[i]=P[i].y=read();
    }
    int k=read();
    pre(w,k);
    std::sort(X,X+w);
    int xsiz=std::unique(X,X+w)-X;
    std::sort(Y,Y+w);
    int ysiz=std::unique(Y,Y+w)-Y;
    for(int i=0;i<w;++i){
        ++Xc[P[i].x=find(X,X+xsiz,P[i].x)];
        ++Yc[P[i].y=find(Y,Y+ysiz,P[i].y)];
    }
    std::sort(P,P+w,cmpY);
    int ans=0,lc=0;
    for(int i=0;i<w;++i){
        if(i && P[i].y==P[i-1].y){
            ++lc;
            int sum=query(P[i].x-1)-query(P[i-1].x);
            int mul=C[lc][k]*C[Yc[P[i].y]-lc][k];
            ans+=sum*mul;
        }
        else lc=0;
        int x=P[i].x,u=Xcnt[x],d=Xc[x]-Xcnt[x];
        int delta=C[u+1][k]*C[d-1][k]-C[u][k]*C[d][k];
        ++Xcnt[x];
        add(P[i].x,xsiz,delta);
    }	
    printf("%d\n",fix(ans));
    return 0;
}

