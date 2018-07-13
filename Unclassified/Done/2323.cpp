#include <cstdio>
#include <algorithm>
#include <vector>
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
struct Edge{
	int id,u,v,c1,c2;
} E[20010];
bool cmp1(const Edge& lhs,const Edge& rhs){
	return lhs.c1<rhs.c1;
}
bool cmp2(const Edge& lhs,const Edge& rhs){
	return lhs.c2<rhs.c2;
}
int fa[10001];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
std::vector<int> res;
bool check(int n,int m,int k,int mid,bool out=false){
	for(int i=1;i<=n;++i)fa[i]=i;
	std::sort(E+1,E+m+1,cmp1);
	int block=n;
	for(int i=1;i<=m && E[i].c1<=mid && block>1 && n-block<k;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			if(out)res.push_back(E[i].id<<1);
			--block;
		}
	}
	if(n-block!=k)
		return false;
	if(block==1)
		return true;
	std::sort(E+1,E+m+1,cmp2);
	for(int i=1;i<=m && E[i].c2<=mid && block>1;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			if(out)res.push_back(E[i].id<<1|1);
			--block;
		}
	}
	return block==1;
}
int main(){
	int n=read();
	int k=read();
	int m=read();
#ifdef ONLINE_JUDGE
	--m;
#endif
	int l=1<<30,r=0;
	for(int i=1;i<=m;++i){
		E[i].id=i;
		E[i].u=read();
		E[i].v=read();
		E[i].c1=read();
		E[i].c2=read();
		l=std::min(l,std::min(E[i].c1,E[i].c2));
		r=std::max(r,std::max(E[i].c1,E[i].c2));
	}
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(n,m,k,mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	res.reserve(n-1);
	check(n,m,k,ans,true);
	std::sort(res.begin(),res.end());
	for(int i=0;i<res.size();++i)
		printf("%d %d\n",res[i]>>1,(res[i]&1)+1);
	return 0;	
}

