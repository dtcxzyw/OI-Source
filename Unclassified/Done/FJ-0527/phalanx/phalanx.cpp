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
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar('\n');
}
const int size=300001;
struct Point{
	int x,y;
	long long ans;	
} q[size];
int main(){
	freopen("phalanx.in","r",stdin);
	freopen("phalanx.out","w",stdout);
	int n=read();
	int m=read();
	int k=read();
	for(int i=0;i<k;++i){
		int x=read();
		int y=read();
		q[i].x=x,q[i].y=y;
		bool flag=true;
		for(int j=i-1;j>=0;--j){
			if(q[j].x==x && q[j].y<=y && y<m)++y;
			else if(y==m && q[j].x<=x && x<n)++x;
			else if(x==n && y==m)x=q[j].x,y=q[j].y;
			if(x==q[j].x && y==q[j].y){
				flag=false;
				q[i].ans=q[j].ans;
				break;
			}
		}
			
		if(flag)q[i].ans=static_cast<long long>(x-1)*m+y;
		print(q[i].ans);
	}
	return 0;
}

