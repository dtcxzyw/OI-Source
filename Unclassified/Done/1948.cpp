#include <cstdio>
#include <queue>
struct Edge{
	int to,next,w;
} E[20010];
const int size=1001;
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
typedef std::pair<int,int> State;
int maxv[size];
bool check(int l,int k,int n){
	for(int i=1;i<=n;++i)maxv[i]=-1;
	std::queue<State> q;
	q.push(std::make_pair(1,k)); 
	while(q.size()){
		State u=q.front();
		q.pop();
		if(u.first==n)return true;
		for(int i=last[u.first];i;i=E[i].next){
			State st;
			st.first=E[i].to;
			st.second=u.second-(E[i].w>l);
			if(st.second>maxv[st.first])
				q.push(st),maxv[st.first]=st.second;
		}
	}
	return false;
}
int main(){
	int n,p,k;
	scanf("%d%d%d",&n,&p,&k);
	int u,v,w,l=0,r=0;
	for(int i=0;i<p;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
		if(w>r)r=w;
	}
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,k,n))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}

