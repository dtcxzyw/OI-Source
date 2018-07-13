#include <cstdio>
bool read(){
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	return c=='1';
}
int a,b,c;
int get(int x,int y,int z){
	return (x*b+y)*c+z;
}
bool flag[6000];
bool check(int bx,int by,int bz,int ex,int ey,int ez){
	if(ex>=a || ey>=b || ez>=c)return false;
	int res=0;
	for(int i=bx;i<=ex;++i)
		for(int j=by;j<=ey;++j)
			if(flag[get(i,j,ez)]){
				++res;
				goto point1;
			}
	point1:
	for(int i=bx;i<=ex;++i)
		for(int j=bz;j<=ez;++j)
			if(flag[get(i,ey,j)]){
				++res;
				goto point2;
			}
	point2:
	if(res==0)return false;
	if(res==2)return true;
	for(int i=by;i<=ey;++i)
		for(int j=bz;j<=ez;++j)
			if(flag[get(ex,i,j)])return true;	
	return false;
}
void reset(int bx,int by,int bz,int size){
	int ex=bx+size,ey=by+size,ez=bz+size;
	for(int i=bx;i<ex;++i)
		for(int j=by;j<ey;++j)
			for(int k=bz;k<ez;++k)
				flag[get(i,j,k)]=false;
}
int foo(){
	scanf("%d%d%d",&a,&b,&c);
	for(int i=0;i<a;++i)
		for(int j=0;j<b;++j)
			for(int k=0;k<c;++k)
				flag[get(i,j,k)]=read();
	int res=0;
	for(int i=0;i<a;++i)
		for(int j=0;j<b;++j)
			for(int k=0;k<c;++k)
				if(flag[get(i,j,k)]){
					int size=1;
					while(check(i,j,k,i+size,j+size,k+size))++size;
					reset(i,j,k,size);
					res+=size;
				}
	return res;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)printf("%d\n",foo());
	return 0;
}


