#include <cstdio>
int A[2][100001]={},n;
void add(int x,int p){
	while(x<=n){
		++A[p][x];
		x+=x&-x;
	}
}
int query(int x,int p){
	int ans=0;
	while(x){
		ans+=A[p][x];
		x-=x&-x;
	}
	return ans;
}
int main(){
    int m;
    scanf("%d%d",&n,&m);
    int c,l,r;
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&c,&l,&r);
        if(c==1)add(l,0),add(r,1);
        else printf("%d\n",query(r,0)-query(l-1,1));
    }
    return 0;
}

