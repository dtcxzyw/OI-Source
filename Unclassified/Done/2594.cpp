#include <cstdio>
int read(){
	int c;
	do c=getchar();
	while(c!='H' && c!='T');
	return c;
}
int sg(int i,int j){
	if(i && j)return i+j;
	int k=i+j+1,cnt=0;
	while(!(k&(1<<cnt)))++cnt;
	return cnt;
}
bool foo(){
	bool flag[256]={};
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j)
			if(read()=='T')
				flag[sg(i,j)]^=1;
	}
	for(int i=0;i<n+m;++i)
		if(flag[i])return true;
	return false;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)puts(foo()?"-_-":"=_=");
	return 0;
}

