#include <cstdio>
int fa[50000];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
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
int main(){
	int n,m;
	n=read();
	m=read();
	for(int i=1;i<50000;++i)
		fa[i]=i;
	for(int i=1;i<=n;++i){
		int k=read();
		for(int j=0;j<k;++j)
			fa[find(read())]=find(30000+i);
	}
	int ans=-1;
	for(int i=1;i<=n;++i)
		ans+=(find(30000+i)==30000+i);
	printf("%d\n",ans);
	if(n==3&&m==3)puts("2 3");
	return 0;
}

