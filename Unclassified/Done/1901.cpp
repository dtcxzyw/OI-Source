#include <cstdio>
const int size=1000001;
int st[size],ssiz=0,h[size],v[size],tot[size]={};
void modify(int i){
	while(ssiz && h[st[ssiz-1]]<=h[i])--ssiz;
	if(ssiz)tot[st[ssiz-1]]+=v[i];
	st[ssiz++]=i;
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
	int n=read();
	for(int i=1;i<=n;++i){
		h[i]=read();
		v[i]=read();
	}
	for(int i=1;i<=n;++i)modify(i);
	ssiz=0;
	for(int i=n;i>=1;--i)modify(i);
	int ans=0;
	for(int i=1;i<=n;++i)
		if(tot[i]>ans)
			ans=tot[i];
	printf("%d\n",ans);
	return 0;
}

