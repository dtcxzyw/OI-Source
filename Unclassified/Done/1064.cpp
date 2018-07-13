#include <cstdio>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int v[61],p[61],q[61],child[61][2]={},dp[61][3201]={};
void buy(int x,int v,int w){
	if(dp[x][v]<w)dp[x][v]=w;
}
void move(int x,int v,int add,int n){
	for(int i=0;i<=n-v;++i)
		buy(x,i+v,dp[x-1][i]+add);
}
int main(){
	int n,m;
	n=read()/10;
	m=read();
	for(int i=1;i<=m;++i){
		v[i]=read();
		p[i]=read()*v[i];
		v[i]/=10;
		if(q[i]=read()){
			if(child[q[i]][0])child[q[i]][1]=i;
			else child[q[i]][0]=i;
		}
	}
	int x=0;
	for(int i=1;i<=m;++i)
		if(!q[i]){
			++x;
			move(x,0,0,n);//
			move(x,v[i],p[i],n);//0
			if(child[i][0])move(x,v[i]+v[child[i][0]],p[i]+p[child[i][0]],n);
			if(child[i][1]){
				move(x,v[i]+v[child[i][1]],p[i]+p[child[i][1]],n);
				move(x,v[i]+v[child[i][0]]+v[child[i][1]],p[i]+p[child[i][0]]+p[child[i][1]],n);
			}
		}
	printf("%d\n",dp[x][n]);
	return 0;
}

