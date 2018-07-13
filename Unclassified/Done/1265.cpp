#include <cstdio>
#include <cmath>
#include <cstring>
int P[5000][2];
bool flag[5000]={};
long long ndis[5000];
long long dis(int a,int b){
	long long dx=P[a][0]-P[b][0],dy=P[a][1]-P[b][1];
	return dx*dx+dy*dy;
}
void update(int i,int n){
	for(int j=0;j<n;++j)
		if(!flag[j]){
			long long d=dis(i,j);
			if(ndis[j]>d)ndis[j]=d;
		}
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d%d",&P[i][0],&P[i][1]);
    memset(ndis,0x3f,sizeof(ndis));
	double ans=0.0;
	flag[0]=true;
	update(0,n);
	for(int i=1;i<n;++i){
		int v=-1;
		long long minv=1LL<<60;
		for(int j=0;j<n;++j)if(!flag[j] && ndis[j]<minv)minv=ndis[j],v=j;
		ans+=sqrt(minv);
		flag[v]=true;
		update(v,n);
	}
    printf("%.2lf",ans);
    return 0;
}

