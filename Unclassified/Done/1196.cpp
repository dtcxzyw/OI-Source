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
int getOp(){
	int c;
	do c=getchar();
	while(c!='M'&&c!='C');
	return c;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
inline void print(int x){
	printImpl(x);
	putchar('\n');
}
const int n=30000,size=n+100;
int fa[size],d[size],end[size];
int find(int x){
	if(fa[x]!=x){
		int old=fa[x];
		int nf=find(old);
		if(nf!=old){
			d[x]+=d[old];
			fa[x]=nf;
		}
	}
	return fa[x];
}
int iabs(int x){
	return x>=0?x:-x;
}
int main(){
	for(int i=1;i<=n;++i)fa[i]=end[i]=i,d[i]=0;
	int t=read();
	for(int i=0;i<t;++i){
		int op=getOp();
		int u=read();
		int v=read();
		if(op=='M'){
			int fu=find(u),fv=find(v);
			fa[fu]=end[fv];
			d[fu]=1;
			end[fv]=end[fu];
			//printf("begin %d end %d\n",fu,end[fv]);
		}
		else{
			if(u==v)puts("0");
			else{
				int fu=find(u),fv=find(v);
				//printf("Info %d %d %d %d\n",fu,fv,d[u],d[v]);
				if(fu==fv)print(iabs(d[u]-d[v])-1);
				else puts("-1");
			}
		}
	}
	return 0;
}

