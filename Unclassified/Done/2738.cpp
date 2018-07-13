#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
int link[210][210],dis[210][210];
struct Node{
	char to[9];
	Node(){
		for(int i=0;i<9;++i)to[i]=120;
	}
	bool operator<(Node rhs) const{
		for(int i=0;i<9;++i)
			if(to[i]!=rhs.to[i])
				return to[i]<rhs.to[i]; 
		return false;
	}
};
std::map<Node,int> vert;
int cnt=0;
int getID(Node x){
	int& id=vert[x];
	if(id==0)id=++cnt;
	return id;
}
void CAS(int& a,int b){
	if(a>b)a=b;
}
int main(){
	int n;
	scanf("%d",&n);
	memset(link,0x1f,sizeof(link));
	for(int i=0;i<n;++i){
		int id,w,l,r,x;
		scanf("%d%d%d%d",&id,&w,&l,&r);
		Node a,b;
		a.to[0]=b.to[0]=id;
		for(int j=1;j<=l;++j){
			scanf("%d",&x);
			a.to[j]=x;
		}
		std::sort(a.to,a.to+l+1);
		for(int j=1;j<=r;++j){
			scanf("%d",&x);
			b.to[j]=x;
		}
		std::sort(b.to,b.to+r+1);
		int ia=getID(a),ib=getID(b);
		link[ia][ib]=link[ib][ia]=w;
	}
	for(int i=1;i<=cnt;++i)link[i][i]=0;
	memcpy(dis,link,sizeof(dis));
	int ans=1<<30;
	for(int k=1;k<=cnt;++k){
		for(int i=1;i<k;++i)
			for(int j=i+1;j<k;++j)
				CAS(ans,dis[i][j]+link[i][k]+link[k][j]);
		for(int i=1;i<=cnt;++i)
			for(int j=1;j<=cnt;++j)
				CAS(dis[i][j],dis[i][k]+dis[k][j]);
	}
	printf("%d\n",ans);
	return 0;
}

