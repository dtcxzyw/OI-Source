#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
const int size=101;
struct Edge{
	int to,next;
	double w;
} E[(size*size<<5)+size*12+10];
int last[500],cnt;
void addEdge(int u,int v,double w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}

const int SS=1,ST=2;

int q[500];
double dis[500];
bool flag[500];
void SPFA(){
	memset(flag,0,sizeof(flag));
	for(int i=0;i<500;++i)
		dis[i]=1e10;
	int b=0,e=1;
	flag[SS]=true;
	q[0]=SS;
	dis[SS]=0.0;
	while(b!=e){
		int u=q[b];
		b=(b+1)%500;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			double nd=dis[u]+E[i].w;
			if(dis[E[i].to]>nd){
				dis[E[i].to]=nd;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%500;
				}
			}
		}
	}
}


struct Point{
	int x,y;
	double dis(Point rhs) const{
		int dx=x-rhs.x,dy=y-rhs.y;
		return sqrt(dx*dx+dy*dy);
	}
	Point operator-(Point rhs) const{
		return Point{x-rhs.x,y-rhs.y};
	}
	Point operator+(Point rhs) const{
		return Point{x+rhs.x,y+rhs.y};
	}
	bool test(Point rhs) const{
		return x*rhs.x+y*rhs.y==0;
	}
};
struct City{
	int t;
	Point p[4];
	void calc(){
		static const int arr[3][3]={
		{0,1,2},
		{1,0,2},
		{2,0,1}};
		for(int i=0;i<3;++i){
			Point d1=p[arr[i][1]]-p[arr[i][0]];
			Point d2=p[arr[i][2]]-p[arr[i][0]];
			if(d1.test(d2)){
				std::swap(p[arr[i][0]],p[2]);
				break;
			}
		}
		p[3]=p[0]+p[1]-p[2];
	}
} c[size];

double foo(){
	memset(last,0,sizeof(last));
	cnt=0;
	int s,t,a,b;
	scanf("%d%d%d%d",&s,&t,&a,&b);
	for(int i=1;i<=s;++i){
		for(int j=0;j<3;++j)
			scanf("%d%d",&c[i].p[j].x,&c[i].p[j].y);
		c[i].calc();
		scanf("%d",&c[i].t);
	}
	
	for(int i=1;i<=s;++i){
		for(int j=0;j<4;++j){
			int idu=i<<2|j;
			for(int k=i+1;k<=s;++k)
				for(int l=0;l<4;++l){
					int idv=k<<2|l;
					double d=c[i].p[j].dis(c[k].p[l])*t;
					addEdge(idu,idv,d);
					addEdge(idv,idu,d);
				}
		}
		
		for(int j=0;j<4;++j)
			for(int k=j+1;k<4;++k){
					double d=c[i].p[j].dis(c[i].p[k])*c[i].t;
					addEdge(i<<2|j,i<<2|k,d);
					addEdge(i<<2|k,i<<2|j,d);
			}
	}
	
	for(int i=0;i<4;++i){
		addEdge(SS,a<<2|i,0.0);
		addEdge(b<<2|i,ST,0.0);
	}
	
	SPFA();
	return dis[ST];
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--)
		printf("%.1lf\n",foo());
	return 0;
}

