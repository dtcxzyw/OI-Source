#include <cstdio>
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
bool foo(){
    int n=read();
    int res=0,last=0,mask=n&1;
    for(int i=1;i<=n;++i){
        int val=read();
        if((i&1)==mask)res^=val-last;
        last=val;
    }
    return res;
}
int main(){
    int t=read();
    while(t--)puts(foo()?"TAK":"NIE");
    return 0;
}

