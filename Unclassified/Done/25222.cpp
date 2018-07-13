#include<cstdio>
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
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar('\n');
}
int minv(int a,int b){
	return a<b?a:b;
}
const int size=50100;
int prime[size],pcnt=0,u[size],sum[size];
bool flag[size]={};
void pre(int n){
	u[1]=1;
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[++pcnt]=i,u[i]=-1;
		for(int j=1;j<=pcnt && i*prime[j]<=n;++j){
			flag[i*prime[j]]=true;
			if(i%prime[j])u[i*prime[j]]=-u[i];		
			else{
				u[i*prime[j]]=0;
				break;
			} 
		}
	}
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+u[i];
}
long long calc(int n,int m){
	int minm=minv(n,m);
	if(minm==0)return 0;
	long long res=0;
	int nxt=0;
	for(int i=1;i<=minm;i=nxt+1){
		int n1=n/(n/i),n2=m/(m/i);
		nxt=minv(n1,n2);
		res+=1LL*(n/i)*(m/i)*(sum[nxt]-sum[i-1]);
	}
	return res;
}
void foo(){
    int a=read()-1;
    int b=read();
    int c=read()-1;
    int d=read();
    int k=read();
    a/=k,b/=k,c/=k,d/=k;
	long long res=calc(b,d)-calc(a,d)-calc(b,c)+calc(a,c);
	print(res);    
}
int main(){
	pre(50000);
    int n=read();
    for(int i=0;i<n;++i)foo();
    return 0;
}

