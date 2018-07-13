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
int main(){
	int t=read();
	while(t--){
		int n=read(),cnt=0,x;
		for(int i=0;i<n;++i){
			int y=read();
			if(!cnt)x=y;
			if(x==y)++cnt;
			else --cnt;
		}
		printf("%d\n",x);
	}	
	return 0;
}

