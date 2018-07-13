#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
const int size=101;
std::vector<std::pair<int,int> > E[size];
void addEdge(int u,int v,int w){
	E[u].push_back(std::make_pair(w,v));
}
int c[size],t,ans=1<<30,cnt=1<<18;
std::bitset<size> flag,link[size];
void DFS(int u,int w){
	--cnt;
	if(w>=ans || cnt<0)return;
	if(u==t)ans=w;
	else if(flag.count() && E[u].size()){
		std::bitset<size> old=flag;
		flag&=link[c[u]];
		for(int i=0;i<E[u].size();++i){
			int v=E[u][i].second;
			if(flag[c[v]])
				DFS(v,w+E[u][i].first);
		}
		flag=old;
	}
}
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
int main(){
	int n,k,m,s;
	n=read();k=read();m=read();s=read();t=read();
	for(int i=1;i<=n;++i)c[i]=read();
	for(int i=1;i<=k;++i){
		for(int j=1;j<=k;++j)
			link[i][j]=(read()==0);
		link[i][i]=false;
	}
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		if(link[c[v]][c[u]])addEdge(u,v,w);
		if(link[c[u]][c[v]])addEdge(v,u,w);
	}
	for(int i=1;i<=n;++i)std::sort(E[i].begin(),E[i].end());
	for(int i=1;i<=n;++i)
		flag[i]=true;
	DFS(s,0);
	if(ans==1<<30)puts("-1");
	else printf("%d\n",ans);
	return 0;
}

