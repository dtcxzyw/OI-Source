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
const int size=200010;
int dp[size],l[size],r[size],q[size],b=0,e=0;
void push(int id){
	if(dp[id]==-1)return;
	while(b<e && dp[q[e-1]]<=dp[id])--e;
	q[e++]=id;
}
int main(){
	int n,m;
	n=read();
	m=read();
	for(int i=1;i<=n+1;++i)l[i]=0,r[i]=i-1;
	for(int i=0;i<m;++i){
		int x=read();
		int y=read();
		l[y+1]=std::max(l[y+1],x);
		r[y]=std::min(r[y],x-1);
	}
	for(int i=1;i<=n+1;++i)l[i]=std::max(l[i],l[i-1]);
	for(int i=n;i>=1;--i)r[i]=std::min(r[i],r[i+1]);
	for(int i=1;i<=n+1;++i){
		for(int j=r[i-1];j<=r[i];++j)push(j);
		while(b<e && q[b]<l[i])++b;
		if(b<e)dp[i]=dp[q[b]]+(i<=n);
		else dp[i]=-1;
	}
	printf("%d\n",dp[n+1]);
	return 0;
}

