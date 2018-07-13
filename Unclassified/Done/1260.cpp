#include <cstdio>
#include <cstring>
const int size=10011;
struct Edge{
	int to,next,w;
} E[30011];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int read(){
	int res=0,c;
	bool flag=false;
	do {
		c=getchar();
		flag|=c=='-';
	}while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int dis[size];
bool flag[size]={};
bool SPFA(int x){
    flag[x]=true;
    for(int i=last[x];i;i=E[i].next){
        if(dis[E[i].to]>dis[x]+E[i].w){
            if(flag[E[i].to])return false;
            dis[E[i].to]=dis[x]+E[i].w;
            if(!SPFA(E[i].to))return false;
        }
    }
    flag[x]=false;
    return true;
}

int main(){
	int n,m;
	n=read();
	m=read();
	int c,u,v,w;
	for(int i=0;i<m;++i){
		c=read();u=read();v=read();
		if(c!=3)w=read();
		switch(c){
			case 1:addEdge(u,v,-w);break;
			case 2:addEdge(v,u,w);break;
			case 3:{addEdge(u,v,0);addEdge(v,u,0);}break;
		}
	}
	for(int i=1;i<=n;++i)
		addEdge(0,i,0);
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	puts(SPFA(0)?"Yes":"No");
	return 0;
}

