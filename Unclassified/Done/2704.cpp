#include <cstdio>
#include <cstring>
int dp[101][100][100],list[100],num[100];
int bitcount(int i){
	int res=0;
	while(i){
		++res;
		i-=i&-i;
	}
	return res;
}
int getLine(){
	int res=0,c;
	do c=getchar();
	while(c!='H' && c!='P');
	while(c=='H'||c=='P'){
		res=(res<<1)+(c=='P');
		c=getchar();
	}
	return res;
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int cnt=0,maxm=1<<m;
	for(int i=0;i<maxm;++i){
		if(i&(i<<1) || i&(i<<2))continue;
		list[cnt]=i;
		num[cnt]=bitcount(i);
		cnt++;
	}
	memset(dp,0xc0,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=1;i<=n;++i){
		int now=getLine();
		for(int j=0;j<cnt;++j){
			if((list[j]|now)!=now)continue;
			for(int k=0;k<cnt;++k){
				if(list[k]&list[j])continue;
				for(int l=0;l<cnt;++l){
					if(list[j]&list[l])continue;
					if(list[k]&list[l])continue;
					CAS(dp[i][j][k],dp[i-1][k][l]+num[j]);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<cnt;++i)
		for(int j=0;j<cnt;++j)
			if(ans<dp[n][i][j])
				ans=dp[n][i][j];
	printf("%d\n",ans);
	return 0;
}

