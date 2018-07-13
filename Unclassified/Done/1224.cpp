#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int size=100100;
int A[size][110];
bool check(int u,int v,int m,int k){
	int res=0;
	for(int i=1;i<=m;++i)
		res+=A[u][i]*A[v][i];
	return res%k==0;
}
int sum[110][110]={};
int test(int x,int m){
	int res=0;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j){
			int mul=A[x][i]*A[x][j];
			res+=sum[i][j]*mul;
			sum[i][j]+=mul;
		}
	return res;
}
int id[size];
int main(){
	int n=read();
	int m=read();
	int k=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)
			A[i][j]=read()%k;
		id[i]=i;
	}
	for(int x=0;x<=10;++x){
		std::random_shuffle(id+1,id+n+1);
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;++i)if(test(id[i],m)%k!=(i-1)%k)
			for(int j=1;j<i;++j)
				if(check(id[i],id[j],m,k)){
					if(id[i]>id[j])std::swap(i,j);
					printf("%d %d\n",id[i],id[j]);
					return 0;
				}
	}
	puts("-1 -1");
	return 0;
}

