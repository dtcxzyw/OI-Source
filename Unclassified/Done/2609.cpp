#include <cstdio>
#include <cstring>
const int mod=100000000,half=mod/2;
char buf[256];
void readi(int& a,int l,int r){
	a=0;
	for(int i=l;i<r;++i)
		a=a*10+buf[i]-'0';
}
int maxv(int a,int b){
	return a>b?a:b;
}
struct BigNum{
	int num[15],siz;
	BigNum(int x=0):siz(1){
		for(int i=0;i<15;++i)num[i]=0;
		num[1]=x;
	}
	void read(){
		scanf("%s",buf);
		int l=strlen(buf),r;
		siz=1;
		while(true){
			r=l,l=r-8;
			readi(num[siz],maxv(l,0),r);
			if(l>0)siz++;
			else break;
		}
	}
	bool test() const{
		return num[1]&1;
	}
	void update(){
		for(int i=1;i<=siz;++i)
			if(num[i]>=mod){
				num[i]-=mod;
				++num[i+1];
			}
		if(num[siz+1])++siz;
	}
	void operator+=(const BigNum& rhs){
		siz=maxv(siz,rhs.siz);
		for(int i=1;i<=siz;++i)
			num[i]+=rhs.num[i];
		update();
	}
	void rightMove(){
		for(int i=siz;i>=1;--i){
			if(i>0 && (num[i]&1))num[i-1]+=mod;
			num[i]>>=1;
		}
		if(!num[siz])--siz;
	}
	void print() const{
		printf("%d",num[siz]);
		for(int i=siz-1;i>=1;--i)
			printf("%08d",num[i]);
		puts("");
	}
};
bool flag[500];
void foo(){
	BigNum num;
	num.read();
	if(num.siz==1 && num.num[1]<=1){
		num.print();
		return;
	}
	BigNum a(1),b(1);
	int cnt=0;
	while(num.siz>1 || num.num[1]>1){
		flag[++cnt]=num.test();
		num.rightMove();
	}
	for(int i=cnt;i>=1;--i)
		if(flag[i]) a+=b;
		else b+=a;
	a.print();
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)foo();
	return 0;
}

