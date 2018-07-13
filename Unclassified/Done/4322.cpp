#include <cstdio>
#include <algorithm>
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
const int size=2505;
struct Edge{
    int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
int S[size],P[size],k;
double w,dp[size][size];
int DFS(int u,int depth){
	int base=u!=0;
    memset(dp[u],0xc2,sizeof(double)*(k+1));
    if(base)dp[u][1]=P[u]-w*S[u];
    else dp[u][0]=0.0;
    int siz=base;
    if(depth<k){
	    int ext=k-depth+1;
		for(int i=last[u];i;i=E[i].next){
	        int v=E[i].to;
	        int csiz=DFS(v,depth+1);
	        for(int a=std::min(ext-1,siz);a>=base;--a){
	            int end=std::min(csiz,ext-a);
				for(int b=1;b<=end;++b)
	                dp[u][a+b]=std::max(dp[u][a+b],dp[u][a]+dp[v][b]);
	        }
	        siz+=csiz;
	    }
	}
    return siz;
}
int main(){
    k=read();
    int n=read();
    for(int i=1;i<=n;++i){
        S[i]=read();
        P[i]=read();
		addEdge(read(),i);
    }
    double l=0,r=1e4;
    while(r-l>=1e-5){
        w=(l+r)*0.5;
        DFS(0,0);
        if(dp[0][k]>=-1e-10)l=w;
        else r=w;
    }
    printf("%.3lf",(l+r)*0.5);
    return 0;
}

