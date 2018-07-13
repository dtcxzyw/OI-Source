#include <cstdio>
int sg(int x,int y){
	int res=0,vis[500]={};
	for(int i=1;i<x;++i)
		vis[sg(i,x-i)]=true;
	for(int i=1;i<y;++i)
		vis[sg(i,y-i)]=true;
	for(int i=0;i<500;++i)
		if(!vis[i])
			return i;
}
int ssg(int x,int y){
	long long res=0,half=1,mod=2;
	while(true){
		if(x%mod<half && y%mod<half)return res;
		half<<=1;
		mod<<=1;
		++res;
	}
}
int main(){
	for(int i=1;i<=10;++i){
		for(int j=1;j<=10;++j)
			printf("(%d,%d)",sg(i,j),ssg(i-1,j-1));
		puts("");
	}
	return 0;
}

