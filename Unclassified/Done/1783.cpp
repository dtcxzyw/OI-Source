#include <cstdio>
#include <algorithm>
const int size=800,SS=801,ST=802;
struct Point{
	int x,y;
	bool operator<(Point rhs) const{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
	double distance(Point rhs) const{
		double dx=x-rhs.x,dy=y-rhs.y;
		return dx*dx+dy*dy;
	}
} P[size];
int n,m,fa[size+3];
double dis[size][size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool check(double r){
	fa[SS]=SS,fa[ST]=ST;
	for(int i=0;i<m;++i){
		fa[i]=i;
		if(P[i].x<=r)fa[find(SS)]=i;
		if(n-P[i].x<=r)fa[find(ST)]=i;
		if(find(SS)==find(ST))return true;
	}
	r*=r*4.0;
	for(int i=0;i<m;++i){
		int fi=find(i);
		for(int j=i+1;j<m;++j){
			int fj=find(j);
			if(fi!=fj && dis[i][j]<=r){
				fa[fj]=fi;
				if(find(SS)==find(ST))return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
		scanf("%d%d",&P[i].x,&P[i].y);
	std::sort(P,P+m);
	for(int i=0;i<m;++i)
		for(int j=i+1;j<m;++j)
			dis[i][j]=P[i].distance(P[j]);
	double l=0.0,r=1000.0;
	while(r-l>1e-4){
		double mid=(l+r)/2.0;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.2lf",l);
	return 0;
}

