#include <cstdio>
#include <cstring>
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
const int size=1010;
int A[1001],dp[size][size],up[2][size][size];
int minv(int a,int b){
	return a<b?a:b;
}
void foo(){
    memset(up,0,sizeof(up));
    int n=read();
    for(int i=1;i<=n;++i)A[i]=A[i-1]+(dp[i][i]=up[0][i][i]=up[1][i][i]=read());
    for(int i=2;i<=n;++i)
        for(int r=i;r<=n;++r){
            int l=r-i+1,all=A[r]-A[l-1];
            dp[l][r]=all-minv(0,minv(up[0][l][r-1],up[1][l+1][r]));
        	up[0][l][r]=minv(up[0][l][r-1],dp[l][r]);
        	up[1][l][r]=minv(up[1][l+1][r],dp[l][r]);
		}
    printf("%d\n",dp[1][n]);
}
int main(){
    int t=read();
    for(int i=0;i<t;++i)foo();
    return 0;
}

