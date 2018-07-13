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
const int size=400005;
struct Range{
    int l,r,id;
    bool operator<(const Range& rhs) const{
        return l<rhs.l;
    }
} A[size];
int nxt[size][20]={},ans[size]={};
int main(){
    int n=read();
    int m=read();
    int cnt=0;
    for(int i=1;i<=n;++i){
        int l=read();
        int r=read();
        if(r<l)r+=m;
        ++cnt;
        A[cnt].l=l,A[cnt].r=r,A[cnt].id=i;
        ++cnt;
        A[cnt].l=l+m,A[cnt].r=r+m,A[cnt].id=0;
    }
    
    std::sort(A+1,A+cnt+1);

    int now=cnt;
    for(int i=cnt-1;i;--i){
        while(A[now].l>A[i].r)--now;
        nxt[i][0]=now;
    }

    for(int i=1;i<20;++i)
        for(int j=1;j<=cnt;++j)
            nxt[j][i]=nxt[nxt[j][i-1]][i-1];

    for(int i=1;i<=cnt;++i)
        if(A[i].id){
            int end=A[i].l+m,cur=i;
            for(int j=19;j>=0;--j){
                int p=nxt[cur][j];
                if(p && A[p].r<end){
                    cur=p;
                    ans[A[i].id]+=1<<j;
                }
            }
        }

    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]+2);

    return 0;
}

