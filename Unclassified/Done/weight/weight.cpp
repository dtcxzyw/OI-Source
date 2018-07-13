#include <cstdio>
#include <cmath>
using namespace std;
int x[1000],y[1000],w[1000];
int main(){
	int n,i;
	scanf("%d\n",&n);
	double sx,sy;
	sx=sy=0.0;
	for(i=0;i<n;++i)
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
	double sumx=1.0,sumy=1.0,dx,dy,dis;
	while(sumx*sumx+sumy*sumy>=1e-6){
		sumx=sumy=0.0f;
		for(i=0;i<n;++i){
			dx=sx-x[i];dy=sy-y[i];
			dis=hypot(dx,dy);
			if(dis==0.0)dis=1.0;
			sumx+=dx*w[i]/dis;
			sumy+=dy*w[i]/dis;
		}
		sx-=sumx/2.0f,sy-=sumy/2.0f;
	}
	printf("%.3lf %.3lf\n",sx,sy);
	return 0;
}

