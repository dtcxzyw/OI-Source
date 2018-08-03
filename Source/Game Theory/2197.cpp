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
    int n=read(),res=0;
    while(n--)res^=read();
    return res;
}
int main(){
    int t=read();
    while(t--)puts(foo()?"Yes":"No");
    return 0;
}

