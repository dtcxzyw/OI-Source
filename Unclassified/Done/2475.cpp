#include <cstdio>
#include <algorithm>
const int size=60,nil=55;
int L[size]={},R[size]={},fa[size]={},root,ans[size],top=0;
int main(){
	int n;
	scanf("%d",&n);
	fa[0]=nil;
	for(int i=1;i<=n;++i){
		int p;
		scanf("%d",&p);
		if(p<100)L[p]=i,fa[i]=p;
		else R[p-100]=i,fa[i]=p-100;
	}
	root=0;
	for(int i=n;i>=0;--i){
		int x=root;
		while(R[x])x=L[x];
		if(L[x] && !L[L[x]] && !R[L[x]])x=L[x];
		ans[top++]=x;
		if(x==root)root=L[x];
		int p=fa[x];
		L[p]=L[x];
		if(L[x])fa[L[x]]=p;
		while(p!=nil){
			std::swap(L[p],R[p]);
			p=fa[p];
		}
	}
	while(top)printf("%d ",ans[--top]);
	return 0;
}

