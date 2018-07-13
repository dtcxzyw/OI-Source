#include <cstdio>
#include <queue>
const int size=5001;
struct Edge{
	int to,next;
	double w;
} E[2][200001];
int last[2][5001]={},cnt[2]={};
void addEdge(int u,int v,double w,int i){
	++cnt[i];
	Edge& r=E[i][cnt[i]];
	r.to=v,r.next=last[i][u],r.w=w;
	last[i][u]=cnt[i];
}
double dis[size];
bool flag[size]={};
int q[size*5];
void SPFA(int n){
	for(int i=1;i<n;++i)dis[i]=1e20;
	dis[n]=0.0,flag[n]=true,q[0]=n;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		flag[u]=false;
		for(int i=last[1][u];i;i=E[1][i].next){
			int v=E[1][i].to;
			if(dis[v]>dis[u]+E[1][i].w){
				dis[v]=dis[u]+E[1][i].w;
				if(!flag[v]){
					flag[v]=true;
					q[e++]=v;
				}
			}
		}
	}
}
struct Node{
	double f,g;
	int p;
	bool operator<(const Node& rhs) const{
		return f==rhs.f?g>rhs.g:f>rhs.f;
	}
};
int main(){
	int n,m;
	double e;
	scanf("%d%d%lf",&n,&m,&e);
	e+=1e-6;
	int u,v;
	double w;
	for(int i=0;i<m;++i){
		scanf("%d%d%lf",&u,&v,&w);
		addEdge(u,v,w,0);
		addEdge(v,u,w,1);
	}
	SPFA(n);
	int ans=0;
	std::priority_queue<Node> q;
	Node s;
	s.f=dis[1];
	s.g=0.0;
	s.p=1;
	q.push(s);
	while(q.size()){
		Node u=q.top();
		q.pop();
		if(u.p==n){
			if(e>=u.g)e-=u.g,++ans;
			else break;
		}
		for(int i=last[0][u.p];i;i=E[0][i].next){
			Node node;
			node.p=E[0][i].to;
			node.g=u.g+E[0][i].w;
			node.f=node.g+dis[node.p];
			q.push(node);
		}
	}
	printf("%d\n",ans);
	return 0;
}

