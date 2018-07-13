#include <cstdio>
#include <cstring>
bool flag[5000],mark[5000];
int foo(int k,int n){
	memset(mark,0,sizeof(mark));
	int res=0,cnt=0;
	for(int i=0;i<n-k+1;++i){
		if((cnt+flag[i])&1){
			++res;
			mark[i]=true;
		}
		cnt+=mark[i];
		if(i-k+1>=0)cnt-=mark[i-k+1];
	}
	for(int i=n-k+1;i<n;++i){
		if((cnt+flag[i])&1)return 1<<30;
		if(i-k+1>=0)cnt-=mark[i-k+1];
	}
	return res;
}
int main(){
	int n;
	scanf("%d",&n);
	char c[2];
	for(int i=0;i<n;++i){
		scanf("%s",c);
		flag[i]=(*c=='B');
	}
	int ans=1<<30,k;
	for(int i=1;i<=n;++i){
		int t=foo(i,n);
		if(t<ans)ans=t,k=i;
	}
	printf("%d %d",k,ans);
	return 0;
}

