#include <cstdio>
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
const int size=100100;
std::map<int,int> dp[size];
typedef std::map<int,int>::iterator IterT;
int b[size],c[size],l[size],maxc[size]={};
long long maxv(long long a,long long b){
	return a>b?a:b;
}
void CASmin(int& a,int b){
	if(a>b)a=b;
}
void CASmax(int& a,int b){
	if(a<b)a=b;
}
int& get(std::map<int,int>& src,int x){
	IterT it=src.find(x);
	if(it==src.end())return src[x]=1<<30;
	return it->second;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		b[i]=read();
		c[i]=read();
		l[i]=read();
	}
	for(int i=1;i<=n;++i)dp[i][0]=0,dp[i][1]=c[i];
	for(int i=n;i>=1;--i){
		int p=b[i];
		std::map<int,int> src=dp[p];
		for(IterT it=src.begin();it!=src.end();++it)
			for(IterT j=dp[i].begin();j!=dp[i].end();++j){
				int val=it->second+j->second;
				if(val<=m)CASmin(get(dp[p],it->first+j->first),val);
				else break;
			}
	}
	long long ans=0;
	for(int i=n;i>=1;--i){
		CASmax(maxc[i],dp[i].rbegin()->first);
		CASmax(maxc[b[i]],maxc[i]);
		long long val=1LL*maxc[i]*l[i];
		if(ans<val)ans=val;
	}
	printf("%lld\n",ans);
	return 0;
}

