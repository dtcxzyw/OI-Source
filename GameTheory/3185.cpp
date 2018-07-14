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
const int size=25,maxSG=2*size;
int sg[size],A[size];
int main(){
    for(int i=1;i<size;++i){
        bool vis[maxSG]={};
        for(int j=0;j<i;++j)
            for(int k=0;k<=j;++k)
                vis[sg[j]^sg[k]]=true;
        for(int j=0;j<maxSG;++j)
            if(!vis[j]){
                sg[i]=j;
                break;
            }
    }
    int t=read();
    while(t--){
        int n=read(),ans=0;
        for(int i=1;i<=n;++i){
            A[i]=read();
            if(A[i]&1)ans^=sg[n-i];
        }
        if(ans==0)puts("-1 -1 -1\n0");
        else{
            int cnt=0;
            for(int i=1;i<=n;++i)if(A[i])
                for(int j=i+1;j<=n;++j)
                    for(int k=j;k<=n;++k)
                        if((ans^sg[n-i]^sg[n-j]^sg[n-k])==0){
                            ++cnt;
                            if(cnt==1)printf("%d %d %d\n",i-1,j-1,k-1);
                        }
            printf("%d\n",cnt);
        }
    }
    return 0;
}

