#include <cstdio>
#include <map>
const int size=11,inf=1<<30;
int n,m,cur[size],A[2][size][size],cnt=0,sum=0;
long long s=0,end=0;
#define asInt64(x) static_cast<long long>(x)
typedef std::map<long long,int> Map;
typedef Map::iterator IterT;
Map cache;
int dfs(int alpha,int beta){
    if(s==end)return sum;
    {
        IterT it=cache.find(s);
        if(it!=cache.end() //&& it->second>=beta
		)return it->second;
    }
    for(int i=1;i<=n;++i)
        if(cur[i-1]>cur[i]){
        	s^=asInt64(cur[i])<<(4*i);
            ++cur[i];
            s^=asInt64(cur[i])<<(4*i);
            ++cnt;
            int x=A[cnt&1][i][cur[i]];
            sum+=x;
            
            int val=-dfs(-beta,-alpha);
            
            sum-=x;
            --cnt;
            s^=asInt64(cur[i])<<(4*i);
            --cur[i];
            s^=asInt64(cur[i])<<(4*i);
            
            //if(val>=beta)return cache[s]=beta;
            if(val>alpha)alpha=val;
        }
    return cache[s]=alpha;
}
int main(){
	freopen("test.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            scanf("%d",&A[0][i][j]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            scanf("%d",&A[1][i][j]);
        	A[1][i][j]=-A[1][i][j];
		}
	for(int i=1;i<=n;++i)
		end|=asInt64(m)<<(4*i);
    cur[0]=m;
    for(int i=1;i<=n;++i)cur[i]=0;
    printf("%d\n",dfs(-inf,inf));
    return 0;
}

