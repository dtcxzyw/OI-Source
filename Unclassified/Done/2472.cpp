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
int readBit(){
    int c;
    do c=getchar();
    while(c<'0'||c>'9');
    return c-'0';
}
int readMark(){
    int c;
    do c=getchar();
    while(c!='L'&&c!='.');
    return c;
}
const int size=4000,SS=size-1,ST=size-2;
struct Edge{
    int to,next,c;
} E[100000];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int c){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c;
    last[u]=cnt;
}
void addEdge(int u,int v,int c){
    addEdgeImpl(u,v,c);
    addEdgeImpl(v,u,0);
}
int n,d[size],q[size];
bool BFS(){
    memset(d,0,sizeof(d));
    d[SS]=1,q[0]=SS;
    int b=0,e=1;
    while(b!=e){
        int u=q[b++];
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            if(!d[v] && E[i].c>0){
                d[v]=d[u]+1;
                q[e++]=v;
            }
        }
    }
    return d[ST];
}
int now[size];
int minv(int a,int b){
    return a<b?a:b;
}
int DFS(int u,int f){
    if(u==ST || f==0)return f;
    int nf=0,k;
    for(int& i=now[u];i;i=E[i].next){
        int v=E[i].to;
        if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].c)))>0){
            E[i].c-=k,E[i^1].c+=k;
            f-=k,nf+=k;
            if(f==0)break;
        }
    }
    return nf;
}
int A[25][25];
struct Point{
	int x,y;
} off[100];
int getID(int x,int y,int m,int t,int st){
	return ((x*m+y)*4+t)*2+st;
}
bool flag[25][25]={};
int main(){
    int n=read();
    int m=read();
    int d=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			A[i][j]=readBit();
			for(int k=1;k<=A[i][j];++k)
				addEdge(getID(i,j,m,k,0),getID(i,j,m,k,1),1);
		}
	int ocnt=0;
	for(int i=-d;i<=d;++i)
		for(int j=-d;j<=d;++j)
			if(i*i+j*j<=d*d){
				++ocnt;
				off[ocnt].x=i,off[ocnt].y=j;
			}
			
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(A[i][j])
			for(int k=1;k<=ocnt;++k){
				int cx=i+off[k].x,cy=j+off[k].y;
				if(cx<=0 || cx>n || cy<=0 || cy>m){
					if(!flag[i][j]){
						flag[i][j]=true;
						for(int c=1;c<=A[i][j];++c)
							addEdge(getID(i,j,m,c,1),ST,1);
					}
				}
				else if(A[cx][cy]){
					for(int c1=1;c1<=A[i][j];++c1)
						for(int c2=1;c2<=A[cx][cy];++c2)
							addEdge(getID(i,j,m,c1,1),getID(cx,cy,m,c2,0),1);
				}
			}
	int siz=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(readMark()=='L'){
				++siz;
				addEdge(SS,getID(i,j,m,A[i][j],0),1);
			}
    int mf=0;
    while(BFS()){
        memcpy(now,last,sizeof(now));
        mf+=DFS(SS,1<<30);
    }
    printf("%d\n",siz-mf);
    return 0;
}

