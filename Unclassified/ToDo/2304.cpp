#include <cstdio>
#include <vector>
#include <algorithm>
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
const int size=50005,S=size-1,T=size-2,psiz=size*2;
struct Point{
	int x,y;
} P[size];
bool cmpX(int lhs,int rhs){
	return P[lhs].x<P[rhs].x;
}
bool cmpY(int lhs,int rhs){
	return P[lhs].y<P[rhs].y;
}
typedef bool (*Func)(int,int);
typedef std::vector<int> Array;
struct Map{
	Array vec[size];
	int table[size],siz;
	Map():siz(0){}
	void insert(int x){
		table[siz++]=x;
	}
	void pre(){
		std::sort(table,table+siz);
		siz=std::unique(table,table+siz)-table;
	}
	Array& operator[](int x){
		int pos=std::lower_bound(table,table+siz,x)-table;
		return vec[pos];
	}
	void sort(Func cmp){
		for(int i=0;i<siz;++i)
			std::sort(vec[i].begin(),vec[i].end(),cmp);
	}
} sx,sy,sadd,ssub;
int find(Array& arr,int id,Func cmp){
	return std::lower_bound(arr.begin(),arr.end(),id,cmp)-arr.begin();
}
void insertA(int x,int y){
	sx.insert(x);
	sy.insert(y);
	sadd.insert(x+y);
	ssub.insert(x-y);
}
void insertB(int x,int y,int id){
	sx[x].push_back(id);
	sy[y].push_back(id);
	sadd[x+y].push_back(id);
	ssub[x-y].push_back(id);
}
struct Edge{
	int to,next,f,w;
} E[100*psiz];
int last[psiz]={},cnt=1;
void addEdgeImpl(int u,int v,int f,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f,E[cnt].w=w;
	last[u]=cnt;
}
int offset;
void addEdge(int u,int v,int w){
	addEdgeImpl(u,v,1,w);
	addEdgeImpl(v,u,0,-w);
}
void build(int n){
	for(int i=0;i<=n;++i)
		insertA(P[i].x,P[i].y);
	sx.pre();
	sy.pre();
	sadd.pre();
	ssub.pre();
	for(int i=0;i<=n;++i)
		insertB(P[i].x,P[i].y,i);
	sx.sort(cmpY);
	sy.sort(cmpX);
	sadd.sort(cmpX);
	ssub.sort(cmpX);
	for(int i=0;i<=n;++i){
		addEdge(S+offset,i,0);
		addEdge(i,i+offset,1);
		addEdge(i+offset,T,0);
		int src=i+offset;
		{
			Array& vx=sx[P[i].x];
			int posX=find(vx,i,cmpY);
			for(int j=posX+1;j<vx.size();++j)
				addEdge(src,vx[j],0);
		}
		{
			Array& vy=sy[P[i].y];
			int posY=find(vy,i,cmpX);
			for(int j=0;j<vy.size();++j)
				if(j!=posY)
					addEdge(src,vy[j],0);
		}
		{
			Array& vadd=sadd[P[i].x+P[i].y];
			int posAdd=find(vadd,i,cmpX);
			for(int j=posAdd-1;j>=0;--j)
				addEdge(src,vadd[j],0);
		}
		{
			Array& vsub=ssub[P[i].x-P[i].y];
			int posSub=find(vsub,i,cmpX);
			for(int j=posSub+1;j<vsub.size();++j)
				addEdge(src,vsub[j],0);
		}
	}
}
int dis[psiz],eid[psiz],q[psiz];
bool flag[psiz]={};
bool SPFA(int src){
	memset(dis,0xc0,sizeof(dis));
	int b=0,e=1;
	q[0]=src,dis[src]=0;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%psiz;
		for(int i=last[u];i;i=E[i].next){
			if(E[i].f){
				int v=E[i].to;
				int d=dis[u]+E[i].w;
				if(dis[v]<d){
					dis[v]=d;
					eid[v]=i;
					if(!flag[v]){
						flag[v]=true;
						q[e]=v;
						e=(e+1)%psiz;
					}
				}
			}
		}
	}
	return dis[T]!=0xc0c0c0c0;
}
int MCMF(){
	int res=0,src=S+offset;
	while(SPFA(src)){
		int mf=1<<30,p=T;
		while(p!=src){
			int id=eid[p];
			mf=std::min(mf,E[id].f);
			p=E[id^1].to;
		}
		p=T;
		while(p!=src){
			int id=eid[p];
			E[id].f-=mf;
			E[id].f+=mf;
			p=E[id^1].to;
		}
		res+=dis[T]*mf;
	}
	return res;
}
int main(){
	printf("%d\n",(sizeof(Map)*4+sizeof(E))>>20);
	int n=read();
	offset=n+1;
	P[0].x=P[0].y=0;
	for(int i=1;i<=n;++i){
		P[i].x=read();
		P[i].y=read();
	}
	build(n);
	printf("%d\n",MCMF());
	return 0;
}

