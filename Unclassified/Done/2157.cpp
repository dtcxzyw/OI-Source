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
const int size=1010;
int t[size],b[size],dp[size][1<<8][16];
void CAS(int& a,int b){
    if(a>b)a=b;
}
int calc(int a,int b){
    return a?t[a]^t[b]:0;
}
int& get(int i,int j,int k){
    return dp[i][j][k+8];
}
int foo(){
    int n=read();
    b[0]=7;
    for(int i=1;i<=n;++i){
        t[i]=read();
        b[i]=read();
    }
    memset(dp,0x3f,sizeof(dp));
    get(1,0,-1)=0;
    for(int i=1;i<=n;++i){
        for(int j=0;j<256;++j)
            for(int k=-8;k<8;++k){
                int val=get(i,j,k);
                if(val!=0x3f3f3f3f){
                    if(j&1)CAS(get(i+1,j>>1,k-1),val);
                    else{
                        int r=1<<30;
                        for(int x=0;x<=7 && i+x<=r;++x)
                            if(!(j&(1<<x))){
                                CAS(r,i+x+b[i+x]);
                                int s=j|(1<<x);
                                CAS(get(i,s,x),val+calc(i+k,i+x));
                            }
                    }
                }
            }
    }
    int res=1<<30;
    for(int i=-8;i<0;++i)
        CAS(res,get(n+1,0,i));
    return res;
}
int main(){
    int t=read();
    for(int i=0;i<t;++i)printf("%d\n",foo());
    return 0;
}

