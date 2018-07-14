#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=2005;
int n,c[size],cache[size][size];
int query(int d,int maxop){
    if(maxop<=0)return 0;
    if(cache[d][maxop]==-1){
        int res=0;
        for(int i=1;i<=maxop;++i){
            int end=d+i;
            res=std::max(res,c[d]-query(end,std::min(i<<1,n-end+1)));
        }
        cache[d][maxop]=res;	
    }
    return cache[d][maxop];
}
int main(){
    memset(cache,-1,sizeof(cache));
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&c[i]);
    for(int i=n;i>=1;--i)
        c[i]+=c[i+1];
    printf("%d\n",query(1,std::min(n,2)));
    return 0;
}

