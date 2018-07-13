#include <cstdio>
const int size=1000005;
int bcnt[size];
bool vis[size]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<=n;++i){
		bcnt[i]=bcnt[i>>1]+(i&1);
		if(i%3==0)vis[bcnt[i]]=true;
	}
	for(int i=0;i<=40;++i)
		if(vis[i])
			printf("%d\n",i);
	return 0;
}

