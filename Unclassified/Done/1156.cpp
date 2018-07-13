#include <cstdio>
#include <algorithm>
#include <cstring>
struct Info{
	int t,f,h;
	bool operator<(const Info& rhs) const{
		return t<rhs.t;
	}
} in[101];
int dp[2][101];
void CAS(int& a,int b,bool& f){
	if(a<b)a=b,f=true;
}
int main(){
	int H,n;
	scanf("%d%d",&H,&n);
	for(int i=1;i<=n;++i)scanf("%d%d%d",&in[i].t,&in[i].f,&in[i].h);
	std::sort(in+1,in+n+1);
	memset(dp,0xc0,sizeof(dp));
	dp[0][0]=10;
	int c,l,sub;
	for(int i=1;i<=n;++i){
		c=i&1,l=!c,sub=in[i].t-in[i-1].t;
		bool flag=false;
		memset(dp[c],0xc0,sizeof(dp[c]));
		for(int j=0;j<=H;++j)
			if(dp[l][j]>=sub)
				CAS(dp[c][j],dp[l][j]+in[i].f-sub,flag);
		for(int j=0;j<=H-in[i].h;++j)
			if(dp[l][j]>=sub)
				CAS(dp[c][j+in[i].h],dp[l][j]-sub,flag);
				
		if(dp[c][H]>=0){
			printf("%d\n",in[i].t);
			return 0;
		}
		
		if(!flag){
			int maxv=-1<<30;
			for(int j=0;j<=H;++j)
				if(maxv<dp[l][j])
					maxv=dp[l][j];
					
			printf("%d\n",in[i-1].t+maxv);
			return 0;	
		}
	}
	int maxv=-1<<30;
	for(int j=0;j<=H;++j)
		if(maxv<dp[c][j])
			maxv=dp[c][j];
			
	printf("%d\n",in[n].t+maxv);
	return 0;	
}

