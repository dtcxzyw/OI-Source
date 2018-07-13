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
const int size=20000100;
int prime[1300000],pcnt=0;
bool flag[size]={};
void pre(int n){
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[pcnt++]=i;
		for(int j=0;j<pcnt && prime[j]*i<=n;++j){
			flag[prime[j]*i]=true;
			if(i%prime[j]==0)break;
		}
	}
}
const int mod=20170408;
int pool[55][201*201]={};
int* allocMat(){
	static int cnt=0;
	return pool[cnt++];
}
struct Mat{
	int *v,n,m;
	Mat(int a,int b):v(allocMat()),n(a),m(b){}
	Mat& operator=(const Mat& rhs){
		v=rhs.v;
		n=rhs.n;
		m=rhs.m;
		return *this;	
	}
	int* operator[](int i){
		return v+i*m;
	}
	const int* operator[](int i) const{
		return v+i*m;
	}
};
void matMul(const Mat& lhs,const Mat& rhs,Mat& res){
	for(int i=0;i<lhs.n;++i)
		for(int j=0;j<rhs.m;++j)
			for(int k=0;k<lhs.m;++k)
				res[i][j]=(res[i][j]+static_cast<long long>(lhs[i][k])*rhs[k][j])%mod;
}
void matMul(Mat& lhs,const Mat& rhs){
	Mat res(lhs.n,rhs.m);
	matMul(lhs,rhs,res);
	lhs=res;
}
int cnt[100],primeCnt[100]={};
int main(){
	int n=read();
	int m=read();
	int p=read();
	for(int i=0;i<p;++i){
		int begin=(i==0?p:i);
		int len=m-begin;
		if(len<0)cnt[i]=0;
		else cnt[i]=1+len/p;
	}
	pre(m);
	for(int i=0;i<pcnt;++i)
		++primeCnt[prime[i]%p];
	int siz=p*2+1;
	Mat ans(1,siz),mul(siz,siz);
	for(int i=0;i<p;++i){
		ans[0][i+1]=cnt[i]-primeCnt[i];
		ans[0][i+p+1]=primeCnt[i];
	}
	for(int i=0;i<p;++i){
		for(int j=0;j<p;++j){
			int offset=(j-i+p)%p;
			mul[i+1][j+1]=cnt[offset]-primeCnt[offset];
			mul[i+1][j+p+1]=primeCnt[offset];
			mul[i+p+1][j+p+1]=cnt[offset];
		}
	}
	--n;
	while(n){
		if(n&1)matMul(ans,mul);
		n>>=1,matMul(mul,mul);
	}
	printf("%d\n",ans[0][p+1]);
	return 0;
}

