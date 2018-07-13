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
int key[10000][100],f[10000][100],cnt[10000]={};
int main(){
	int n,m,s;
	n=read();
	m=read();
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			f[i][j]=read();
			if(f[i][j])++cnt[i];
			key[i][j]=read();
		}
	}
	s=read();
	int ans=0;
	for(int i=0;i<n;++i){
		ans=(ans+key[i][s])%20123;
		int r=key[i][s]%cnt[i]+cnt[i];
		for(int j=f[i][s];j<r;){
			if(++s==m)s=0;
			j+=f[i][s];
		}
	}
	printf("%d\n",ans);
	return 0;
}

