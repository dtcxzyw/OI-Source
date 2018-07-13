#include <cstdio>
#include <algorithm>
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
int iabs(int x){
	return x>0?x:-x;
}
struct Info{
	int t,x,y;
	bool check(Info src) const{
		return t-src.t>=iabs(x-src.x)+iabs(y-src.y);
	}	
} info[10000];
int len[10000];
int main(){
	int n=read();
	int m=read();
	int ans=0;
	for(int i=0;i<m;++i){
		info[i].t=read();
		info[i].x=read();
		info[i].y=read();
		len[i]=1;
		for(int j=0;j<i;++j)
			if(len[i]<len[j]+1 && info[i].check(info[j]))
				len[i]=len[j]+1;
		if(len[i]>ans)ans=len[i];
	}
	printf("%d\n",ans);
	return 0;
}

