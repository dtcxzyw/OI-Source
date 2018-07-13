#include <cstdio>
#include <map>
#include <vector>
#include <set>
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
const int size=1<<20;
long long encode(long long x,int y){
	return (x<<32)|y;
}
void decode(long long c,int& x,int& y){
	x=c>>32;
	y=c&((1LL<<32)-1);
}
std::set<int> dp[size];
int bcnt[size],ans=30;
bool flag;
void move(int s,int l,const std::vector<long long>& src){
	for(int i=0;i<src.size();++i){
		int x,y;
		decode(src[i],x,y);
		if(!(s&(1<<x))){
			int dst=s|(1<<x);
			flag|=dp[dst].insert(y).second;
			printf("%d %d\n",x,y);
			if(y==l && ans>bcnt[dst])
				ans=bcnt[dst];
		}
	}
}
int main(){
	int n=read();
	int l=read();
	typedef std::map<int,std::vector<long long> > MapT;
	typedef MapT::iterator IterT;
	MapT info;
	for(int i=0;i<n;++i){
		int d=read();
		int c=read();
		for(int j=0;j<c;++j){
			int t=read();
			info[t].push_back(encode(i,std::min(t+d,l)));
		}
	}
	int end=1<<n;
	for(int s=0;s<end;++s)
		bcnt[s]=bcnt[s>>1]+(s&1);
	dp[0].insert(0);
	do{
		flag=false;
		for(int s=0;s<end;++s){
			int old=dp[s].size();
			for(std::set<int>::iterator i=dp[s].begin();i!=dp[s].end();++i){
				IterT it=info.find(*i);
				printf("move %d %d\n",s,*i);
				if(it!=info.end())
					move(s,l,it->second);
			}
		}
		printf("end\n");
	}while(flag);
	if(ans<=n)printf("%d\n",ans);
	else puts("-1");
	return 0;
}

