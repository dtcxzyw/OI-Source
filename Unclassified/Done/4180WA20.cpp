#include <cstdio>
#include <algorithm>
#include <map>
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
const int size=1000005;
std::map<int,int> fa[size];
int find(int u,int t){
	std::map<int,int>::iterator it=fa[u].lower_bound(t);
	--it;
	int& p=it->second;
	return p==u?u:p=find(p,t);
}
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[3*size];
bool flag[3*size]={};
long long base[3*size];
int cnt[3*size],tmp[size];
int findTmp(int u){
	return tmp[u]==u?u:tmp[u]=findTmp(tmp[u]);
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		E[i].u=read();
		E[i].v=read();
		E[i].w=read();
	}	
	std::sort(E,E+m);
	int esiz=n-1;
	for(int i=1;i<=n;++i)fa[i][-1]=i;
	long long minv=0;
	for(int i=0,j=0;i<m && j<esiz;++i){
		int fu=find(E[i].u,i),fv=find(E[i].v,i);
		base[i]=minv,cnt[i]=j;
		if(fu!=fv){
			fa[fu][i]=fv;
			flag[i]=true;
			minv+=E[i].w;
			++j;
		}
	}
	long long ans=1LL<<60;
	for(int i=0;i<m;++i)
		if(flag[i]){
			for(int j=1;j<=n;++j)tmp[j]=find(j,i);
			long long now=base[i];
			for(int j=i+1;j<m && cnt[i]<esiz && now<ans;++j){
				int fu=findTmp(E[j].u),fv=findTmp(E[j].v);
				if(fu!=fv){
					now+=E[j].w;
					tmp[fu]=fv;
					++cnt[i];
				}
			}
			if(cnt[i]==esiz && now<ans && now>minv)ans=now;
		}
	printf("%lld\n",ans);
	return 0;
}

