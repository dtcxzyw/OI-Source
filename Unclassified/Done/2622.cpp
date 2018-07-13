#include <cstdio>
#include <cstring>
const int size=1<<10;
bool link[size][size]={};
int A[10];
int calc(int x,int n){
	for(int i=0;i<n;++i)
		if(A[i]==1)x&=~(1<<i);
		else if(A[i]==-1)x|=(1<<i);
	return x;
}
int dis[size],q[size];
bool flag[size]={};
void SPFA(int end){
	memset(dis,0x3f,sizeof(dis));
	int s=end-1;
	q[0]=s,dis[s]=0,flag[s]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=0;i<end;++i)
			if(link[u][i] && dis[i]>dis[u]+1){
				dis[i]=dis[u]+1;
				if(!flag[i]){
					flag[i]=true;
					q[e]=i;
					e=(e+1)%size;
				}
			}
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int end=1<<n;
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j)scanf("%d",&A[j]);
		for(int s=0;s<end;++s)
			link[s][calc(s,n)]=true;
	}
	SPFA(end);
	if(dis[0]==0x3f3f3f3f)dis[0]=-1;
	printf("%d\n",dis[0]);
	return 0;
}

