#include <cstdio>
#include <algorithm>
const int size=251,mod=10007;
int inv[mod],A[size][size]={};
int solve(int n){
    for(int i=1;i<=n;++i){
        int x=i;
        for(int j=i;j<=n;++j)
            if(A[j][i]%mod!=0){
                x=j;
                break;
            }
        if(x!=i){
            for(int j=i;j<=n;++j)
                std::swap(A[i][j],A[x][j]);
        }
        int invv=inv[(A[i][i]%mod+mod)%mod];
        for(int j=i+1;j<=n;++j){
            int mul=A[j][i]%mod*invv%mod;
            for(int k=i;k<=n;++k)
                A[j][k]=(A[j][k]-A[i][k]%mod*mul)%mod;
        }
    }
    int res=1;
    for(int i=1;i<=n;++i)
        res=res*(A[i][i]%mod)%mod;
    return (res+mod)%mod;
}
int main(){
    inv[1]=1;
    for(int i=2;i<mod;++i)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        ++A[u][u];
        --A[u][v];
    }
    printf("%d\n",solve(n-1));
    return 0;
}

