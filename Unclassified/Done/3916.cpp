#include <cstdio>
const int size=100001;
struct Edge{
	int to,next;
} E[size];
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
int maxi[size]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
	}
	
	top(n);
	for(int i=1;i<=n;++i)
		maxi[i]=i;
		
		
	bool flag=true;
	while(flag){
		flag=false;
		for(int i=siz;i>=1;--i){
			int x=p[i];
			for(int j=last[x];j;j=E[j].next)
				if(maxi[E[j].to]>maxi[x])
					maxi[x]=maxi[E[j].to],flag=true;
		}
	}
	
	for(int i=1;i<=n;++i)
		printf("%d ",maxi[i]);
	
	return 0;
}

