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
const int size=100005;
char buf[size];
int cnt[size][26]={};
int find(int b,int e,int x){
	int l=b,r=e,res=-1;
	while(l<=r){
		int m=(l+r)>>1;
		if(cnt[e][x]>cnt[m-1][x])res=m,r=m-1;
		else l=m+1;
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	scanf("%s",buf+1);
	for(int i=1;i<=n;++i)buf[i]-='a';
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j)
			cnt[i][j]=cnt[i-1][j]+(buf[i]==j);
	}
	for(int i=0;i<m;++i){
		int a=read();
		int b=read();
		int c=read();
		int d=read();
		int res=0;
		for(int j=c;j<=d;++j){
			int p=find(a,b,buf[j]);
			if(p==-1)break;
			a=p+1;
			++res;
		}
		printf("%d\n",res);
	}
	return 0;
}

