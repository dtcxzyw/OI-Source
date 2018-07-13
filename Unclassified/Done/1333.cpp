#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while((c<'a'||c>'z')&&(c!=EOF));
	if(c==EOF)return 0;
	while('a'<=c&&c<='z'){
		res=res*131+c;
		c=getchar();
	}
	return res;
}
const int size=250010;
int V[size][2],id[size*2],in[size*2]={},fa[size*2];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool merge(int a,int b){
	a=find(a),b=find(b);
	if(a==b)return 0;
	fa[a]=b;
	return 1;
}
int main(){
	int cnt;
	for(cnt=0;(id[cnt<<1]=V[cnt][0]=read())&&(id[cnt<<1|1]=V[cnt][1]=read());++cnt);
	std::sort(id,id+cnt*2);
	int siz=std::unique(id,id+cnt*2)-id;
	for(int i=0;i<siz;++i)fa[i]=i;
	int block=siz;
	for(int i=0;i<cnt;++i){
		int l=std::lower_bound(id,id+siz,V[i][0])-id;
		int r=std::lower_bound(id,id+siz,V[i][1])-id;
		++in[l],++in[r];
		block-=merge(l,r);
	}
	int pcnt=0;
	for(int i=0;i<siz;++i)
		if(in[i]&1)++pcnt;
	if(block<=1 && (pcnt==0 || pcnt==2))puts("Possible");
	else puts("Impossible");
	return 0;
}

