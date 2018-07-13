#include <cstdio>
#include <cstdlib>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100010*2;
int L[size],R[size];
int maxd=0,mind=1<<30,n;
void DFS(int u,int d){
	if(u==-1){
		if(d>maxd)maxd=d;
		if(d<mind)mind=d;
	}
	else{
		DFS(L[u],d+1);
		DFS(R[u],d+1);
	}
}
void noAnswer(){
	puts("-1");
	exit(0);
}
enum Type{
	min,mix,max
};
int ans=0;
Type exchange(int u,int d){
	if(u==-1)return d==mind?min:max;
	else{
		Type l=exchange(L[u],d+1);
		Type r=exchange(R[u],d+1);
		if(l==mix && r==mix)noAnswer();
		if(l<r)++ans;
		if(l==r)return l;
		return mix;
	}
}
bool mark[size]={};
int main(){
	n=read();
	int id=n;
	for(int i=1;i<=n;++i){
		L[i]=read();
		if(L[i]>0)mark[L[i]]=true;
		R[i]=read();
		if(R[i]>0)mark[R[i]]=true;
	}
	int root;
	for(root=1;root<=n;++root)
		if(!mark[root])
			break;
	DFS(root,0);
	if(maxd-mind>1)noAnswer();
	if(mind==maxd)puts("0");
	else{
		exchange(root,0);
		printf("%d\n",ans);	
	}
	return 0;
}

