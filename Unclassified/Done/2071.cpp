#include <cstdio>
#include <cstring>
const int size=4001;
int p[size][2],pair[size][2]={};
bool flag[size]={};
bool match(int u){
	for(int i=0;i<2;++i){
		int v=p[u][i];
		if(!flag[v]){
			flag[v]=true;
			if(!pair[v][0] || match(pair[v][0])){
				pair[v][0]=u;
				return true;
			}
			if(!pair[v][1] || match(pair[v][1])){
				pair[v][1]=u;
				return true;
			}
		}	
	}
	return false;
}
int main(){
	int n,cnt=0;
	scanf("%d",&n);
	n<<=1;
	for(int i=1;i<=n;++i)
		scanf("%d%d",&p[i][0],&p[i][1]);
	for(int i=1;i<=n;++i){
		memset(flag,0,sizeof(flag));
		cnt+=match(i);
	}
	printf("%d\n",cnt);
	return 0;
}

