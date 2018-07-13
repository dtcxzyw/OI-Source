#include <cstdio>
const int size=100001;
struct Edge{
    int to,next;
} E[1000001];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
int p[size],siz=0,in[size]={};
void top(int n){
    for(int i=1;i<=n;++i)
        for(int j=last[i];j;j=E[j].next)
            ++in[E[j].to];
    for(int i=1;i<=n;++i)
        if(in[i]==0)
            p[++siz]=i;
    for(int i=1;i<=n;++i)
        for(int j=last[p[i]];j;j=E[j].next)
            if((--in[E[j].to])==0)
                p[++siz]=E[j].to;
                
    for(int i=1;i<=n;++i)
        if(in[i]!=0)
            p[++siz]=i;
}
int maxw[size],w[size];
bool s[size]={},t[size]={};
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    	scanf("%d",&w[i]);
    int u,v,z;
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&u,&v,&z);
        addEdge(u,v);
        if(z==2)addEdge(v,u);
    }
    
    top(n);
    for(int i=1;i<=n;++i)
        maxw[i]=w[i];
        
    s[1]=t[n]=true;
    
    bool flag=true;
    while(flag){
        flag=false;
        for(int i=siz;i>=1;--i){
            int x=p[i];
            if(!t[x])
            	for(int j=last[x];j;j=E[j].next)
                	if(t[E[j].to])
                    	t[x]=flag=true;
        }
        for(int i=1;i<=siz;++i){
            int x=p[i];
            if(s[x])
            	for(int j=last[x];j;j=E[j].next)
                	if(!s[E[j].to])
                    	s[E[j].to]=flag=true;
        }
    }
    
    flag=true;
    while(flag){
        flag=false;
        for(int i=siz;i>=1;--i){
            int x=p[i];
            if(s[x])
            	for(int j=last[x];j;j=E[j].next)
                	if(t[E[j].to] && maxw[E[j].to]>maxw[x])
                    	maxw[x]=maxw[E[j].to],flag=true;
        }
    }
    
    int ans=0;
    for(int i=1;i<=n;++i)
        if(ans<maxw[i]-w[i])
        	ans=maxw[i]-w[i];
    
    printf("%d\n",ans);
    
    return 0;
}

