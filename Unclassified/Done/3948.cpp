#include <cstdio>
long long read(){
	long long res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int getCode(){
	int c;
	do c=getchar();
	while(c!='A' && c!='Q');
	return c;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	if(x<0)putchar('-'),x=-x;
	printImpl(x);
	putchar('\n');
}
long long mod,maxv,minv;
const int size=80001;
int cnt[size];
long long sum[size],num[size];
void update(int n){
	for(int i=1;i<=n;++i)
		num[i]=num[i-1]+sum[i];
}
int main(){
	int n=read();
	int opt=read();
	mod=read();
	minv=read();
	maxv=read();
	num[0]=sum[0]=0;
	int op,l,r,x;
	for(int i=0;i<opt;++i){
		op=getCode();
		l=read();
		r=read();
		if(op=='A'){
			x=read();
			sum[l]+=x,sum[r+1]-=x;
		}
		else{
			update(r);
			int res=0;
			for(int j=l;j<=r;++j){
				long long v=num[j]*j%mod;
				if(minv<=v && v<=maxv)++res;
			}
			print(res);
		}
	}
	
	update(n);
	
	for(int i=1;i<=n;++i){
		cnt[i]=cnt[i-1];
		long long v=num[i]*i%mod;
		if(minv<=v && v<=maxv)++cnt[i];
	}
	
	int f=read();
	for(int i=0;i<f;++i){
		l=read();
		r=read();
		print(cnt[r]-cnt[l-1]);
	}
	return 0;
}

