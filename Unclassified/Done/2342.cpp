#include <cstdio>
const int size=30001;
int fa[size],siz[size],depth[size];
int find(int x){
	if(fa[x]!=x){
		int p=find(fa[x]);
		depth[x]+=depth[fa[x]]-1;
		fa[x]=p;
	}
	return fa[x];
}
//a->b
void move(int a,int b){
	depth[b]=siz[a]+1;
	siz[a]+=siz[b];
	fa[b]=a;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<size;++i)
		fa[i]=i,siz[i]=depth[i]=1;
	char c[2];
	int x,y;
	for(int i=0;i<n;++i){
		scanf("%s%d",c,&x);
		if(*c=='M'){
			scanf("%d",&y);
			move(find(x),find(y));
		}
		else {
			int p=find(x);
			printf("%d\n",siz[p]-depth[x]);
		}
	}
	return 0;
}

