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
const int size=10001;
struct Edge{
    int to,next,w;
} E[50001*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
    last[u]=cnt;
}
int c[size],q[size],dis[size];
bool flag[size];
bool SPFA(int n,int bi,int mc){
    memset(dis,0xc0,sizeof(dis));
    memset(flag,0,sizeof(flag));
    int b=0,e=1;
    q[0]=1,dis[1]=bi,flag[1]=true;
    
    while(b!=e){
        int u=q[b];
        b=(b+1)%size;
        flag[u]=false;
        
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            int d=dis[u]-E[i].w;
            if(d>=0 && dis[v]<d && c[v]<=mc){
				dis[v]=d;
				if(v==n)return true;
                if(!flag[v]){
                    flag[v]=true;
                    q[e]=v;
                    e=(e+1)%size;
                }
            }
        }
    }
    
    return dis[n]>=0;
}
int main(){
    int n=read();
    int m=read();
    int b=read();
    
    int maxv=0;
    for(int i=1;i<=n;++i){
        c[i]=read();
    	if(c[i]>maxv)
    		maxv=c[i];
	}
	
    int u,v,w;
    for(int i=0;i<m;++i){
        u=read();
        v=read();
        w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    
    int l=c[1],r=maxv,ans=-1;
    while(l<=r){
    	int mid=(l+r)>>1;
    	if(SPFA(n,b,mid))ans=mid,r=mid-1;
    	else l=mid+1;
	}
	
    if(ans==-1)puts("AFK");
    else printf("%d\n",ans);
    return 0;
}



