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
const int size=100010,mod=1000000007;
int sum1[size]={},sum2[size]={};
void add(int* A,int n,int x,int val){
    while(x<=n){
        A[x]=(A[x]+val)%mod;	
        x+=x&-x;
    }
}
int query(int* A,int x){
    int res=0;
    while(x){
        res=(res+A[x])%mod;
        x-=x&-x;
    }
    return res;
}
int A[size],B[size];
int find(int siz,int x){
    return std::lower_bound(B,B+siz,x)-B+1;
}
int last[size]={};
bool flag[size]={};
int main(){
    int n=read();
    for(int i=0;i<n;++i)A[i]=B[i]=read();
    std::sort(B,B+n);
    int siz=std::unique(B,B+n)-B;
    for(int i=0;i<n;++i){
        int p=find(siz,A[i]);
        if(!flag[p])add(sum1,siz,p,1),flag[p]=true;
        long long val=(query(sum2,p-1)+query(sum1,p-1))%mod;
        add(sum2,siz,p,(val-last[p]+mod)%mod);
    	last[p]=val;
    }
    printf("%d\n",query(sum2,siz));
    return 0;
}

