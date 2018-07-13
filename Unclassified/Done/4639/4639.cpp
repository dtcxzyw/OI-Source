#include <cstdio>
#include <cstring>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int getAlpha(){
	int c,res;
	do c=getchar();
	while(c<'A'||c>'Z');
	res=c;
	while('A'<=c&&c<='Z')c=getchar();
	return res;
}
typedef long long BigInt;
const BigInt one=1;
void print(BigInt x){
	if(x>=10)print(x/10);
	putchar('0'+x%10);
}
const int size=100005;
struct Add{
	int dst,src;
} A[size];
struct Mat{
	BigInt val[26][26];
	int n,m;
	Mat(){}
	Mat(int n,int m):n(n),m(m){}
	void reset(){
		memset(val,0,sizeof(val));
	}
	const BigInt* operator[](int id) const{
		return val[id];
	}
	BigInt* operator[](int id){
		return val[id];
	}
	Mat operator*(const Mat& rhs) const{
		Mat res(n,rhs.m);
		for(int i=0;i<res.n;++i)
			for(int j=0;j<res.m;++j){
				BigInt sum=0;
				for(int k=0;k<m;++k)
					sum+=val[i][k]*rhs[k][j];
				res[i][j]=sum;
			}
		return res;
	}
};
const int end=64;
Mat pt[end+1];
Mat powm(BigInt k){
	Mat res=pt[0];
	for(int i=0;i<end;++i)
		if((k>>i)&1)res=res*pt[i];
	return res;
}
int main(){
	Mat base(1,26);
	for(int i=0;i<26;++i)base[0][i]=read();
	Mat trans(26,26);
	trans.reset();
	for(int i=0;i<26;++i)trans[i][i]=1;
	bool flag=true;
	int acnt=1,dst,key;
	long long gate;
	while(flag){
		switch(getAlpha()){
			case 'A':{
				++acnt;
				A[acnt].dst=getAlpha()-'A';
				A[acnt].src=getAlpha()-'A';
				break;
			}
			case 'I':{
				key=getAlpha()-'A';
				gate=read();
				int line=read();
				for(int i=2;i<line;++i)
					base[0][A[i].dst]+=base[0][A[i].src];
				for(int i=line;i<=acnt;++i)
					for(int j=0;j<26;++j)
						trans[j][A[i].dst]+=trans[j][A[i].src];
				break;
			}
			case 'P':{
				flag=false;
				dst=getAlpha()-'A';
				break;
			}
		}
	}
	BigInt l=1,r=-1;
	for(int i=0;i<end;++i){
		if(i==0)pt[i]=trans;
		else pt[i]=pt[i-1]*pt[i-1];
		Mat end=base*pt[i];
		if(end[0][key]>=gate){
			r=one<<i;
			break;
		}
	}
	if(r==-1)throw;
	BigInt ans;
	while(l<=r){
		BigInt m=(l+r)>>1;
		Mat res=base*powm(m);
		if(res[0][key]>=gate)r=m-1,ans=res[0][dst];
		else l=m+1;
	}
	print(ans);
	return 0;
}

