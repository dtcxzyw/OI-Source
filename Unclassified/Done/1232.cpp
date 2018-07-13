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
const int size=200005;
int id[size],dfs[size];
bool flag[size]={};
int main(){
	int n=read();
	for(int i=1;i<=n;++i)id[read()]=i;
	for(int i=1;i<=n;++i)dfs[i]=id[read()];
	int ans=4,l=2,r=n+1,siz=2;
	flag[1]=flag[2]=true;
	for(int i=3;i<=n;++i){
		if(dfs[i]<dfs[i-1])ans+=2;
		else if(dfs[i]==dfs[i-1]+1 && siz==i-1)++ans;
		flag[dfs[i]]=true;
		while(l<r && flag[l+1])++l,++siz;
		while(l<r && flag[r-1])--r,++siz;
	}
	printf("%d.%d00\n",ans>>1,ans&1?5:0);
	return 0;
}

