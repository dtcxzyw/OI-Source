#include <cstdio>
#include <algorithm>
#include <cstring>
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
const int size=205;
struct Seg{
    int l,r;
} A[size];
int cnt[size*2][size*2],L[size*2][size],R[size*2][size],g[size*2][size*2],P[size*2];
int main(){
    int n=read();
    for(int i=0;i<n;++i){
        A[i].l=read();
        P[i<<1]=A[i].l;
        A[i].r=A[i].l+read();
        P[i<<1|1]=A[i].r;
    }
    std::sort(P,P+n*2);
    int siz=std::unique(P,P+n*2)-P;
    for(int i=0;i<n;++i){
        A[i].l=std::lower_bound(P,P+siz,A[i].l)-P;
        A[i].r=std::lower_bound(P,P+siz,A[i].r)-P;
    }
    for(int i=0;i<siz;++i){
        for(int j=0;j<n;++j)
            if(A[j].l>=i)
                ++cnt[i][A[j].r];
        for(int j=1;j<siz;++j)
            cnt[i][j]+=cnt[i][j-1];
    }
    memset(L,0xc0,sizeof(L));
    L[0][0]=0;
    for(int i=0;i<siz;++i){
        for(int j=0;j<=n;++j){
            for(int k=0;k<i;++k)
                L[i][j]=std::max(L[i][j],std::max(L[k][j]+cnt[k][i],
                    j>=cnt[k][i]?L[k][j-cnt[k][i]]:0));
        }
    }
    memset(R,0xc0,sizeof(R));
    R[siz-1][0]=0;
    for(int i=siz-1;i>=0;--i){
        for(int j=0;j<=n;++j){
            for(int k=i+1;k<siz;++k)
                R[i][j]=std::max(R[i][j],std::max(R[k][j]+cnt[i][k],
                    j>=cnt[i][k]?R[k][j-cnt[i][k]]:0));
        }
    }
    memset(g,0xc0,sizeof(g));
    for(int i=0;i<siz;++i){
        for(int j=i;j<siz;++j){
            for(int x=0,y=n;x<=n && y>=0;++x){
                while(y>=0 && x+y>L[i][x]+cnt[i][j]+R[j][y])--y;
                if(y>=0)g[i][j]=std::max(g[i][j],x+y);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;++i)
        ans=std::max(ans,std::min(i,L[siz-1][i]));
    printf("%d\n",ans);
    for(int i=0;i<n;++i){
        int res=0;
        for(int j=0;j<=A[i].l;++j)
            for(int k=A[i].r;k<siz;++k)
                res=std::max(res,g[j][k]);
        printf("%d\n",res);
    }
    return 0;
}

