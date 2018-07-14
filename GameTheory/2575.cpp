#include <cstdio>
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
int sg[1<<20];
int calcSg(int st){
    if(sg[st]==-1){
        bool flag[20]={};
        for(int i=0;i<20;++i){
            int cp=1<<i;
            if(st&cp){
                int clear=~((cp<<1)-1);
                int mask=(~(st&clear))&clear;
                int pos=mask&-mask;
                if(pos<(1<<20)){
                    int dst=st^cp^pos;
                    flag[calcSg(dst)]=true;
                }
            }
        }
        for(int i=0;i<20;++i)
            if(!flag[i]){
                sg[st]=i;
                break;
            }
        }
    return sg[st];
}
bool foo(){
    int n=read(),res=0;
    while(n--){
        int m=read();
        int st=0;
        while(m--)st|=1<<(read()-1);
        res^=calcSg(st);
    }
    return res;
}
int main(){
    memset(sg,-1,sizeof(sg));
    int t=read();
    while(t--)puts(foo()?"YES":"NO");
    return 0;
}

