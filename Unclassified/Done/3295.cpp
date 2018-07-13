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
const int size=100100,mod=1000000007;
int fa[size*17],id[size][17],L[size*17],R[size*17],lut[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int a,int b){
	a=find(a),b=find(b);
	if(a!=b)fa[a]=b;
}
int main(){
	int n=read();
	int m=read();
	lut[1]=0;
	for(int i=2;i<=n;++i)lut[i]=lut[i>>1]+1;
	int cnt=0,end=lut[n];
	for(int k=0;k<=end;++k)
		for(int i=1;i<=n;++i){
			id[i][k]=++cnt;
			fa[cnt]=cnt;
			if(k){
				L[cnt]=id[i][k-1];
				R[cnt]=id[i+(1<<(k-1))][k-1];
			}
		}	
	for(int i=1;i<=m;++i){
		int l1=read();
		int r1=read();
		int l2=read();
		int r2=read();
		int k=lut[r1-l1+1];
		merge(id[l1][k],id[l2][k]);
		merge(id[r1-(1<<k)+1][k],id[r2-(1<<k)+1][k]);
	}
	//push down
	for(int i=cnt;i>n;--i){
		int fi=find(i);
		if(fi!=i){
			merge(L[i],L[fi]);
			merge(R[i],R[fi]);	
		}
	}
	int scnt=0;
	for(int i=1;i<=n;++i)
		scnt+=(find(i)==i);
	long long ans=9;
	for(int i=1;i<scnt;++i)ans=(ans*10)%mod;
	printf("%lld\n",ans);
	return 0;
}

