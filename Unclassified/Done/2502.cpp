#include <cstdio>
#include <algorithm>
int fa[501];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
struct Edge{
	int u,v,w;
	bool operator<(Edge rhs) const{
		return w<rhs.w;
	}
} E[5001];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	std::sort(E,E+m);
	
	int s,t;
	scanf("%d%d",&s,&t);
	
	double ans=1e9;
	int maxv,minv=0;
	for(int i=0;i<m;++i){
		for(int j=1;j<=n;++j)fa[j]=j;
		int cmaxv=0,cminv=1<<30;
		bool flag=false;
		for(int j=i;j<m;++j){
			int fu=find(E[j].u),fv=find(E[j].v);
			if(fu!=fv){
				cmaxv=std::max(cmaxv,E[j].w);
				cminv=std::min(cminv,E[j].w);
				fa[fu]=fv;
				if(find(s)==find(t)){
					flag=true;
					break;
				}
			}
		}
		
		if(flag){
			double r=static_cast<double>(cmaxv)/cminv;
			if(r<ans)
				ans=r,maxv=cmaxv,minv=cminv;
		}
	}
	
	if(minv==0)puts("IMPOSSIBLE");
	else{
		int d=gcd(maxv,minv);
		maxv/=d,minv/=d;
		if(minv==1)printf("%d\n",maxv);
		else printf("%d/%d\n",maxv,minv);
	}
	return 0;
}

