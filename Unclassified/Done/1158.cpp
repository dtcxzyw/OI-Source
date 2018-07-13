#include <cstdio>
#include <algorithm>
struct Point{
	int x,y,d1,md2;
	bool operator<(Point rhs) const{
		return d1<rhs.d1;
	}
} P[100001];
int dis(int x1,int y1,int x2,int y2){
	int dx=x1-x2,dy=y1-y2;
	return dx*dx+dy*dy;
}
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
int main(){
	int x1,y1,x2,y2,n;
	x1=read();
	y1=read();
	x2=read();
	y2=read();
	n=read();
	for(int i=0;i<n;++i){
		P[i].x=read();
		P[i].y=read();
		P[i].d1=dis(P[i].x,P[i].y,x1,y1);
	}
	std::sort(P,P+n);
	for(int i=n-1;i>=0;--i)P[i].md2=std::max(dis(P[i].x,P[i].y,x2,y2),P[i+1].md2);
	int ans=P[0].md2;
	for(int i=0;i<n;++i){
		int w=P[i].d1+P[i+1].md2;
		if(w<ans)ans=w;
	}
	printf("%d\n",ans);
	return 0;
}

