#include <cstdio>
#include <cmath>
int x[4],y[4];
int cross(int a,int b){
	int dxa=x[a]-x[3],dxb=x[b]-x[3],dya=y[a]-y[3],dyb=y[b]-y[3];
	return dxa*dyb-dxb*dya;
}
double dis(int a,int b){
	int dx=x[a]-x[b],dy=y[a]-y[b];
	return sqrt(dx*dx+dy*dy);
}
int foo(){
	for(int i=0;i<3;++i)
		if(x[i]==x[3] && y[i]==y[3])
			return 4;
			
	for(int i=0;i<3;++i)
		if(fabs(dis(i,3)+dis((i+1)%3,3)-dis(i,(i+1)%3))<1e-5)
			return 3;
	
	int cv[3];
	for(int i=0;i<3;++i)
		cv[i]=cross(i,(i+1)%3);
			
	if(cv[0]>0 && cv[1]>0 && cv[2]>0)return 1;
	if(cv[0]<0 && cv[1]<0 && cv[2]<0)return 1;
	return 2;
}
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
	for(int i=0;i<4;++i){
		x[i]=read();
		y[i]=read();
	}
	printf("%d\n",foo());
	return 0;
}

