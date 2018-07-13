#include <cstdio>
int main(){
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;++i){
        int n,m;
        scanf("%d%d",&n,&m);
        int last=(n+m-1)/m;
        puts((n-last)&1?"0":"1");
    }
    return 0;
}

