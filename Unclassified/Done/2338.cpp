#include <cstdio>
#include <algorithm>
int T[10000],D[10000];
int main(){
    int n,v=1,tc=0,dc=0,x,tb=0,db=0;
    double ct=0.0,cs=0.0;
    scanf("%d",&n);
    char c[2];
    for(int i=0;i<n;++i){
        scanf("%s%d",c,&x);
        if(*c=='T')T[tc++]=x;
        else D[dc++]=x;
    }
    std::sort(T,T+tc);
    std::sort(D,D+dc);
    int t,d;
    double tt,td;
    while(tc!=tb || dc!=db){
        int t=tb<tc?T[tb]:100000000,d=db<dc?D[db]:1000000000;
        tt=t-ct,td=(d-cs)*v;
        if(tt==td)
            ++tb,++db,ct=t,cs=d,++v;
        else if(tt<td)
            ++tb,ct=t,cs+=tt/v;
        else
            ++db,ct+=td,cs=d;
        ++v;
    }
    ct+=(1000.0-cs)*v;
    printf("%d\n",static_cast<int>(ct+0.5));
    return 0;    
}

