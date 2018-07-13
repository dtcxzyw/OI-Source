#include <cstdio>
#include <cstdlib>
#include <algorithm>
const int size=1010;
struct Edge{
	int to,next;
} E[2*size*size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int A[size],B[size],smin[size],color[size]={},S1[size],S2[size];
void DFS(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(color[v]){
			if(color[v]==color[u]){
				puts("0");
				exit(0);
			}
		}
		else{
			color[v]=3-color[u];
			DFS(v);
		}
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);
		B[i]=A[i];
	}
	std::sort(B+1,B+n+1);
	smin[n]=0x3f3f3f3f;
	for(int i=n-1;i>0;--i)
		smin[i]=std::min(smin[i+1],A[i+1]);
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(A[i]<A[j] && A[i]>smin[j]){
				addEdge(i,j);
				addEdge(j,i);
			}
	for(int i=1;i<=n;++i)
		if(!color[i]){
			color[i]=1;
			DFS(i);
		}
	int s1=0,s2=0,np=1;
	for(int i=1;i<=n;++i){
		if(color[i]==1)printf("a "),S1[++s1]=A[i];
		else printf("c "),S2[++s2]=A[i];
		while(s1 && S1[s1]==B[np])printf("b "),--s1,++np;
		while(s2 && S2[s2]==B[np])printf("d "),--s2,++np;
	}
	while(s1 && S1[s1]==B[np])printf("b "),--s1,++np;
	while(s2 && S2[s2]==B[np])printf("d "),--s2,++np;
	return 0;
}

