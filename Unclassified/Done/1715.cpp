#include <cstdio>
#include <bitset>
#include <algorithm>
int cnt[301]={},x[301],y[301];
std::bitset<300> flag[300][300];
bool edgeEquation(int a,int b,int c){
	return 1LL*(x[c] - x[a]) * (y[b] - y[a]) > 1LL*(y[c] - y[a]) * (x[b] - x[a]);
}
inline int foo(int i,int j,int k){
	if(flag[j][i][k])std::swap(i,k);
	return (flag[i][j]&flag[j][k]&flag[k][i]).count();
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		x[i]=read();
		y[i]=read();
	}
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			for(int k=j+1;k<n;++k){
					flag[i][k][j]=!(flag[i][j][k]=edgeEquation(i,j,k));
					flag[j][k][i]=!(flag[j][i][k]=edgeEquation(j,i,k));
					flag[k][j][i]=!(flag[k][i][j]=edgeEquation(k,i,j));
				}
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			for(int k=j+1;k<n;++k)
				++cnt[foo(i,j,k)];
	for(int i=0;i<n-2;++i)
		printf("%d\n",cnt[i]);
	return 0;
}

