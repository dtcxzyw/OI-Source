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
const int size=50010;
//X / eat X / X eat
int fa[size*3];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n=read();
	for(int i=1;i<=3*n;++i)fa[i]=i;
	int k=read();
	int ans=0;
	for(int i=0;i<k;++i){
		int op=read();
		int u=read();
		int v=read();
		bool flag=false;
		if(u>n || v>n)flag=true;
		else{
			if(op==1){
				if(find(u)==find(v+n) || find(v)==find(u+n))flag=true;
				else {
					fa[find(u)]=find(v);
					fa[find(u+n)]=find(v+n);
					fa[find(u+n+n)]=find(v+n+n);
				}
			}
			else{
				if(find(u)==find(v) || find(u+n)==find(v))flag=true;
				else{
					fa[find(u)]=find(v+n);
					fa[find(v)]=find(u+n+n);
					fa[find(u+n)]=find(v+n+n);
				}
			}
		}
		ans+=flag;
	}
	printf("%d\n",ans);
	return 0;
}

