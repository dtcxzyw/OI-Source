#include <cstdio>
#include <algorithm>
#include <cstring>
struct Player{
	int w,s,id;
	bool operator<(Player rhs) const{
		return s==rhs.s?id<rhs.id:s>rhs.s;
	}
} P[200001],tmp[200001];
int L[100001],R[100001];
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
	int n=read();
	int r=read();
	int q=read()-1;
	int siz=n*2;
	for(int i=0;i<siz;++i)P[i].s=read(),P[i].id=i+1;
	for(int i=0;i<siz;++i)P[i].w=read();
	std::sort(P,P+siz);
	for(int i=0;i<r;++i){
		for(int j=0;j<n;++j)
			if(P[j<<1].w>P[j<<1|1].w)L[j]=j<<1,R[j]=j<<1|1,++P[j<<1].s;	
			else L[j]=j<<1|1,R[j]=j<<1,++P[j<<1|1].s;	
		int a=0,b=0;
		for(int j=0;j<siz;++j)
			if(a<n && b<n){
				if(P[L[a]]<P[R[b]])tmp[j]=P[L[a++]];
				else tmp[j]=P[R[b++]];
			}
			else if(a<n)tmp[j]=P[L[a++]];
			else tmp[j]=P[R[b++]];
		memcpy(P,tmp,sizeof(P));
	}
	printf("%d\n",P[q].id);
	return 0;
}

