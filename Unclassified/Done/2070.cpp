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
int getCode(){
	int c;
	do c=getchar();
	while(c!='L'&&c!='R');
	return c;
}
struct Node{
	int x,off;
	bool operator<(Node rhs) const{
		return x<rhs.x;
	}
} L[100001*2];
int main(){
	int n=read(),off,x=0;
	for(int i=0;i<n;++i){
		off=read();
		if(getCode()=='L'){
			L[i<<1].x=x-off,L[i<<1].off=1;
			L[i<<1|1].x=x,L[i<<1|1].off=-1;
			x-=off;
		}
		else{
			L[i<<1].x=x,L[i<<1].off=1;
			L[i<<1|1].x=x+off,L[i<<1|1].off=-1;
			x+=off;
		}
	}
	n<<=1;
	std::sort(L,L+n);
	int sum=0,ans=0;
	for(int i=0;i<n;++i){
		if(sum>=2)ans+=L[i].x-L[i-1].x;
		sum+=L[i].off;
	}
	printf("%d\n",ans);
	return 0;
}

