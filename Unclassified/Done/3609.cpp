#include <cstdio>
int toInt(int x){
	switch(x){
		case 'H':return 0;break;
		case 'P':return 1;break;
		case 'S':return 2;break;
	}
}
int dp[2][21][3]={},list[100000];
void CAS(int& x,int y){
	if(x<y)x=y;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	char c[2];
	for(int i=0;i<n;++i){
		scanf("%s",c);
		list[i]=toInt(*c);
	}
	bool now=false,last=true;
	for(int i=0;i<n;++i){
		now=!now,last=!last;
		for(int j=0;j<=k;++j)
			for(int x=0;x<3;++x){
				CAS(dp[now][j][x],dp[last][j][x]+(x==list[i]));
				if(j)for(int y=0;y<3;++y)
					if(x!=y)CAS(dp[now][j][x],dp[last][j-1][y]+(x==list[i]));
			}
	}
	int ans=0;
	for(int j=0;j<=k;++j)
		for(int x=0;x<3;++x)
			CAS(ans,dp[now][j][x]);
	printf("%d\n",ans);
	return 0;
}

