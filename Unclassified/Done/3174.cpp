#include <cstdio>
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
const int size=300010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int dp[size],ans=0;
void DFS(int u,int p){
	int cnt=0,first=0,second=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			DFS(v,u);
			++cnt;
			if(dp[v]>first){
				second=first;
				first=dp[v];
			}
			else if(dp[v]>second)
				second=dp[v];
		}
	}
	if(cnt){
		int num=cnt-(second?2:1)+(p?2:1);
		CAS(ans,first+second+num);
		//printf("ans %d %d %d %d %d\n",u,first,second,num,first+second+num);
		dp[u]=first+cnt;
	}
	else dp[u]=1;
	//printf("dp %d = %d\n",u,dp[u]);
}
int main(){
	int n=read();
	int m=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	printf("%d\n",ans);
	return 0;
}

