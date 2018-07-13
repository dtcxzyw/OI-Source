#include <cstdio>
#include <algorithm>
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
int a[size],b[size],flag[size]={},ans[size];
void color(int id,int alpha){
	flag[id]|=alpha;
}
int lowbit(int id){
	int x=~flag[id];
	return x&-x;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i)a[i]=read()>>1;
	for(int i=1;i<n;++i)b[i]=read()>>1;
	int r=0;
	for(int i=1;i<=n;++i){
		if(i>r){
			ans[i]=lowbit(i);
			r=i;
		}
		{
			int end=i+a[i],k=i<<1;
			for(int j=r+1;j<=end;++j)ans[j]=ans[k-j];
			r=std::max(r,end);
			if(i!=a[i]+1)color(end+1,ans[i-a[i]-1]);
		}
		{
			int end=i+b[i],k=i<<1|1;
			for(int j=r+1;j<=end;++j)ans[j]=ans[k-j];
			r=std::max(r,end);
			if(i!=b[i])color(end+1,ans[i-b[i]]);	
		}
	}
	for(int i=1;i<=n;++i)putchar('a'+__builtin_ctz(ans[i]));
	return 0;
}

