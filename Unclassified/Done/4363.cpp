#include <cstdio>
#include <map>
const int size=11,inf=1<<30;
int n,m,cur[size],A[2][size][size];
long long end=0;
typedef std::map<long long,int> Map;
typedef Map::iterator IterT;
Map cache;
#define asInt64(x) static_cast<long long>(x)
int dfs(long long s,bool now){
	if(s==end)return 0;
	{
		IterT it=cache.find(s);
		if(it!=cache.end())return it->second;
	}
	int res=-inf;
	for(int i=1;i<=n;++i)
		if(cur[i-1]>cur[i]){
			++cur[i];
			res=std::max(res,A[now][i][cur[i]]-dfs(s^(asInt64((cur[i]-1)^cur[i])<<(4*i)),!now));
			--cur[i];
		}
	return cache[s]=res;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&A[0][i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&A[1][i][j]);
	for(int i=1;i<=n;++i)
		end|=asInt64(m)<<(4*i);
	cur[0]=m;
	for(int i=1;i<=n;++i)cur[i]=0;
	printf("%d\n",dfs(0,false));
	return 0;
}

