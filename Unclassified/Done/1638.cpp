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
int cnt[2001]={};
int A[1000001]={};
int main(){
	int n,m;
	n=read();
	m=read();
	for(int i=1;i<=n;++i)A[i]=read();
	int w=1<<30,pa=0,pb=0,num=0;
	for(int l=1,r=1;r<=n;++r){
		if(++cnt[A[r]]==1)++num;
		while(num==m && cnt[A[l]]>1){
			--cnt[A[l]];
			++l;
		}
		if(num==m){
			int cw=r-l;
			if(cw<w || (cw==w && l<pa)) pa=l,pb=r,w=cw;
		}
	}
	printf("%d %d\n",pa,pb);
	return 0;
}

