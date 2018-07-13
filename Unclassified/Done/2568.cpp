#include <cstdio>
const int size=10000010;
int prime[1000010],pcnt;
long long phi[size];
bool flag[size];
void pre(int n){
	phi[1]=1;
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[++pcnt]=i,phi[i]=i-1;
		for(int j=1;j<=pcnt && prime[j]*i<=n;++j){
			flag[prime[j]*i]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
int main(){
	int n;
	scanf("%d",&n);
	pre(n);
	for(int i=2;i<=n;++i)
		phi[i]+=phi[i-1]+phi[i];
	long long ans=0;
	for(int i=1;i<=pcnt;++i){
		int siz=n/prime[i];
		ans+=phi[siz];
	}
	printf("%lld\n",ans);
	return 0;
}

