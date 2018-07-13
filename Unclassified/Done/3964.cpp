#include <cstdio>
#include <algorithm>
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
const int size=100010;
struct Point{
    int x,y;
} P[size];
int X[size],Y[size];
long long SX[size],SY[size];
int main(){
    int n=read();
    if(n<=1){
        puts("0");
        return 0;
    }
    for(int i=0;i<n;++i){
        int x=read();
        int y=read();
        X[i]=P[i].x=x+y;
        Y[i]=P[i].y=x-y;
    }
    std::sort(X,X+n);
    SX[0]=X[0];
    for(int i=1;i<n;++i)
        SX[i]=SX[i-1]+X[i];
    std::sort(Y,Y+n);
    SY[0]=Y[0];
    for(int i=1;i<n;++i)
        SY[i]=SY[i-1]+Y[i];
    long long ans=1LL<<60;
    for(int i=0;i<n;++i){
        int px=std::lower_bound(X,X+n,P[i].x)-X;
        int py=std::lower_bound(Y,Y+n,P[i].y)-Y;
        long long dx=1LL*P[i].x*(px+1)-SX[px]+SX[n-1]-SX[px]-1LL*P[i].x*(n-px-1);
        long long dy=1LL*P[i].y*(py+1)-SY[py]+SY[n-1]-SY[py]-1LL*P[i].y*(n-py-1);
        if(dx+dy<ans)ans=dx+dy;
    }
    printf("%lld\n",ans>>1);
    return 0;
}

