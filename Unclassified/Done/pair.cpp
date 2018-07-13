#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=500010;
int sum[maxn]={},size,n;
long long A[maxn],B[maxn];
int remap(long long x){
    return lower_bound(B+1,B+size+1,x)-B;
}
inline void add(int x){
    while(x<=n){
        ++sum[x];
        x+=x&-x;
    }
}
int get(int i){
    int res=0;
    while(i){
        res+=sum[i];
        i-=i&-i;
    }
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%lld",&A[i]);
    
    memcpy(B+1,A+1,sizeof(long long)*n);
    sort(B+1,B+n+1);
    size=unique(B+1,B+n+1)-(B+1);
    
    long long res=0;
    for(int i=1;i<=n;++i){
        int id=remap(A[i]);
        res+=i-get(id);
        add(id);
    }
    
    printf("%lld\n",res-n);
    return 0;
}

