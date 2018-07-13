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
const int size=100010;
long long sum[size]={};
int src[size][210]={};
struct Info{
	long long d;
	int i;
	Info(){}
	Info(long long dv,int pre):d(dv),i(pre){}
};
class Queue{
private:
	Info mData[size];
	int mBegin,mEnd;
	double slope(Info lhs,Info rhs) const{
		return static_cast<double>(rhs.d-lhs.d)/(sum[rhs.i]-sum[lhs.i]);
	}
public:
	void clear(){
		mBegin=mEnd=0;
	}
	void push(Info val){
		while(mEnd-mBegin>1 && slope(mData[mEnd-2],mData[mEnd-1])<=slope(mData[mEnd-1],val))--mEnd;
		mData[mEnd++]=val;
	}
	Info front(long long ai){
		while(mEnd-mBegin>1 && -ai<=slope(mData[mBegin],mData[mBegin+1]))++mBegin;
		if(mBegin==mEnd)return Info(0,-1);
		return mData[mBegin];
	}
} Q[2];
int FP[size],P[size];
int main(){
	int n=read();
	int m=read();
	int siz=0,fcnt=0;
	for(int i=1;i<=n;++i){
		int x=read();
		if(x){
			++siz;
			P[siz]=i;
			sum[siz]=sum[siz-1]+x;
		}
		else FP[++fcnt]=i;
	}
	Q[0].clear();
	Q[1].clear();
	Q[0].push(Info(0,0));
	long long ans=0,cn=0;
	for(int k=1;k<=m;++k){
		int c=k&1,l=1-c;
		Q[c].clear();
		for(int i=k;i<siz;++i){
			Info pre=Q[l].front(sum[i]);
			if(pre.i!=-1){
				long long val=sum[i]*(sum[siz]-sum[i]+sum[pre.i])+pre.d;
				src[i][k]=pre.i;
				long long d=val-sum[siz]*sum[i];
				Q[c].push(Info(d,i));
				if(k>=m-fcnt && ans<val)
					ans=val,cn=i;
			}
		}	
	}
	printf("%lld\n",ans);
	for(int i=m;cn && i>=1;--i){
		printf("%d ",P[cn]);
		cn=src[cn][i];
		--m;
	}
	for(int i=1;i<=m;++i)
		printf("%d ",FP[i]);
	return 0;
}

