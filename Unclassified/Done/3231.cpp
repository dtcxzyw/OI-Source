#include <cstdio>
#include <algorithm>
bool read(){
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	return c=='1';
}
const int size=6000;
struct Point{
	int x,y,z;
} P[size];
struct Edge{
	int to,next;
} E[size];
int last[size],ecnt=0;
void addEdge(int u,int v){
	++ecnt;
	E[ecnt].to=v,E[ecnt].next=last[u];
	last[u]=ecnt;
}
int timeStamp=0,vis[size]={},pair[size]={};
bool match(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(vis[v]!=timeStamp){
			vis[v]=timeStamp;
			if(pair[v]==-1 || match(pair[v])){
				pair[v]=u;
				return true;
			}
		}
	}
	return false;
}
int calc(int s,int cnt,int a,int b,int c,int test){
	ecnt=0;
	for(int i=0;i<a;++i)last[i]=0;
	for(int i=0;i<b;++i)pair[i]=-1;
	for(int i=1;i<=cnt;++i)if(s&(1<<P[i].z))addEdge(P[i].x,P[i].y);
	int res=c;
	for(int i=0;i<c;++i)
		if(s&(1<<i))--res;
	for(int i=0;i<a && res<test;++i){
		++timeStamp;
		if(match(i))++res;
	}
	return res;
}
int foo(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	int cnt=0;
	for(int i=0;i<a;++i)
		for(int j=0;j<b;++j)
			for(int k=0;k<c;++k)
				if(read()){
					++cnt;
					P[cnt].x=i,P[cnt].y=j,P[cnt].z=k;		
				}
	int mind=std::min(std::min(a,b),c);
	if(c!=mind){
		if(a==mind){
			std::swap(a,c);
			for(int i=1;i<=cnt;++i)std::swap(P[i].x,P[i].z);
		}
		else{
			std::swap(b,c);
			for(int i=1;i<=cnt;++i)std::swap(P[i].y,P[i].z);
		}
	}
	int res=c,end=1<<c;
	for(int i=0;i<end;++i)
		res=std::min(res,calc(i,cnt,a,b,c,res));
	return res;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)printf("%d\n",foo());
	return 0;
}


