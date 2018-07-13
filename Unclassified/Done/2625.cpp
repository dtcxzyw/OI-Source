#include <cstdio>
#include <cmath>
using namespace std;
bool dp[51][360];
int r[51],cnt=0;
char c[10];
int clamp(int x){
	return (x%360+360)%360;
}
int main(){
	int n;
	scanf("%d",&n);
	int v,f=0,b=0;
	for(int i=0;i<n;++i){
		scanf("%s%d",c,&v);
		switch(*c){
		case 'f':f+=v;break;
		case 'b':b+=v;break;
		case 'l':r[++cnt]=v;break;
		case 'r':r[++cnt]=-v;break;
		}
	}
	dp[0][0]=true;
	for(int i=1;i<=cnt;++i){
		for(int j=0;j<360;++j)
			if(dp[i-1][j])
				dp[i][j]=dp[i][clamp(j+r[i])]=true;
	}
	int minv=0;
	for(int i=0;i<=180;++i)
		if(dp[cnt][clamp(180+i)]||dp[cnt][clamp(180-i)]){
			minv=i;
			break;
		}
	double pi=acos(-1.0);
	double rad=minv/180.0*pi;
	double x=sin(rad)*b,y=f+cos(rad)*b;
	double dis=sqrt(x*x+y*y);
	printf("%.6lf\n",dis);
	return 0;
}

