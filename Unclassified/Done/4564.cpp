#include <cstdio>
#include <cstring>
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
const int size=205,mod=998244353;
int add(int a,int b){
	int c=a+b;
	return c<mod?c:c-mod;
}
int sub(int a,int b){
	int c=a-b;
	return c<0?c+mod:c;
}
long long mul(long long a,long long b){
	long long c=a*b;
	return c<mod?c:c%mod;
}
long long inv(long long a){
	long long res=1;
	int k=mod-2;
	while(k){
		if(k&1)res=mul(res,a);
		k>>=1,a=mul(a,a);	
	}
	return res;
}
int m[size],st[size][105]={},obj[size],P[size],invv[size];
void query(){
	int k=read();
	for(int i=1;i<=k;++i)obj[i]=read();
	memset(P,0,sizeof(P));
	P[0]=1;
	for(int i=1;i<=k;++i){
		int u=obj[i],p0=st[u][0],sp=sub(1,p0);
		for(int j=i;j>=1;--j)
			P[j]=add(mul(P[j-1],sp),mul(P[j],p0));
		P[0]=mul(P[0],p0);
	}
	for(int i=1;i<=k;++i){
		int u=obj[i],p0=st[u][0];
		if(p0==1)printf("%d ",0);
		else{
			int sp=sub(1,p0),invsp=inv(sp);
			int sum=0,cur=0;
			for(int j=k;j>=1;--j){
				int cp=sub(P[j],mul(cur,p0));
				cur=mul(cp,invsp);
				sum=add(sum,mul(cp,invv[j]));
			}
			printf("%d ",sum);
		}
	}
	putchar('\n');
}
int main(){
	int n=read();
	invv[1]=1;
	for(int i=2;i<=n;++i)
		invv[i]=mul(mod-mod/i,invv[mod%i]);
	for(int i=1;i<=n;++i){
		m[i]=read();
		st[i][m[i]]=1;
	}
	int q=read();
	for(int i=0;i<q;++i){
		if(read())query();
		else{
			int id=read();
			int u=read();
			int v=read();
			long long p=mul(u,inv(v)),sp=sub(1,p);
			for(int j=0;j<=m[id];++j)
				st[id][j]=add(j?mul(st[id][j],sp):st[id][j],mul(st[id][j+1],p));
		}
	}
	for(int i=1;i<=n;++i){
		int ans=0;
		for(int j=1;j<=m[i];++j)
			ans=add(ans,mul(j,st[i][j]));
		printf("%d ",ans);
	}
	return 0;
}

