#include <cstdio>
const int mod=1000000007,size=5000001;
int cnt[2][size]={},prime[size],pcnt=0;
bool flag[size]={};
void pre(int n){
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[++pcnt]=i;
		for(int j=1;j<=pcnt && prime[j]*i<=n;++j){
			flag[prime[j]*i]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int add(int x,int c){
	int i=0;
	for(i=1;x!=1 && prime[i]<=x;++i)
		while(x%prime[i]==0){
			x/=prime[i];
			++cnt[c][i];
		}
	return i;
}
int main(){
	freopen("fiborial.in","r",stdin);
	freopen("fiborial.out","w",stdout);
	int n;
	scanf("%d",&n);
	pre(n);
	int maxp=0,l,c;
	for(int i=1;i<=n;++i){
		c=i&1,l=!c;
		for(int j=1;j<=maxp;++j)
			cnt[c][j]=(cnt[c][j]+cnt[l][j])%mod;
		int cp=add(i,c);	
		if(cp>maxp)maxp=cp;
	}
	int ans=1;
	for(int i=1;i<=pcnt;++i)
		ans=1LL*ans*(cnt[c][i]+1)%mod;
	printf("%d\n",ans);
	return 0;
}

