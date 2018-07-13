#include <cstdio>
#include <cstring>
const int size=2005;
int A[size];
bool B[size];
int main(){
	freopen("test.in","r",stdin);
	freopen("std.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&A[i]);
	for(int i=1;i<=m;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		memset(B,0,sizeof(B));
		for(int j=l;j<=r;++j)B[A[j]]=true;
		int cur=0;
		while(B[cur])++cur;
		printf("%d\n",cur);
	}
	return 0;
}


