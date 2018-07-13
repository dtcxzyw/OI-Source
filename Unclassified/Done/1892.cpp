#include <cstdio>
int fa[2002];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=(n<<1);++i)
		fa[i]=i;
	char c[2];
	int x,y;
	for(int i=0;i<m;++i){
		scanf("%s%d%d",c,&x,&y);
		if(*c=='F')fa[find(x)]=find(y);
		else{
			fa[find(x+n)]=find(y);
			fa[find(y+n)]=find(x);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		cnt+=find(i)==i;
	printf("%d\n",cnt);
	return 0;
}

