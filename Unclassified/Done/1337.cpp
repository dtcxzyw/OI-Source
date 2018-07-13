#include <cstdio>
#include <cmath>
using namespace std;
int x[1000],y[1000],w[1000];
int main(){
    int n;
    scanf("%d\n",&n);
    double sx=0.0,sy=0.0;
    for(int i=0;i<n;++i){
        scanf("%d%d%d",&x[i],&y[i],&w[i]);
		sx+=x[i],sy+=y[i];
	}
	sx/=n,sy/=n;
    double sumx=1.0,sumy=1.0,dx,dy,dis,mul,p=1e5;
    for(int k=0;k<50;++k){
	    for(int j=0;j<200;++j){
	        sumx=sumy=0.0f;
	        for(int i=0;i<n;++i){
	            dx=x[i]-sx;dy=y[i]-sy;
	            dis=sqrt(dx*dx+dy*dy);
	            if(dis>0.0){
	            	mul=w[i]/dis;
	            	sumx+=dx*mul,sumy+=dy*mul;
	        	}
	        }
	        dis=sqrt(sumx*sumx+sumy*sumy);
	        if(dis<=p)break;
	        sx+=sumx/dis*p,sy+=sumy/dis*p;
	    }
	    p/=2.0;
	}
    printf("%.3lf %.3lf\n",sx,sy);
    return 0;
}

