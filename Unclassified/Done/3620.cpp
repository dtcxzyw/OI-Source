#include <cstdio>
#include <queue>
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
const int size=100005;
struct Info{
	int p;
	long long l;
	Info(int p,long long l):p(p),l(l){}
	bool operator<(const Info& rhs) const{
		return l>rhs.l;
	}
};
int A[size],pre[size],nxt[size];
long long len[size];
bool flag[size]={};
int main(){
	int n=read();
	int k=read();
	for(int i=1;i<=n;++i)A[i]=read();
	std::priority_queue<Info> heap;
	for(int i=2;i<=n;++i){
		len[i]=A[i]-A[i-1];
		heap.push(Info(i,len[i]));
	}
	len[1]=len[n+1]=2000000005;
	for(int i=1;i<=n;++i)pre[i]=i-1;
	for(int i=1;i<=n;++i)nxt[i]=i+1;
	long long res=0;
	for(int i=0;i<k;++i){
		while(flag[heap.top().p])heap.pop();
		Info info=heap.top();
		heap.pop();
		res+=info.l;
		int p=pre[info.p],n=nxt[info.p];
		flag[p]=flag[n]=true;
		nxt[pre[p]]=pre[nxt[n]]=info.p;
		pre[info.p]=pre[p],nxt[info.p]=nxt[n];
		len[info.p]=len[p]+len[n]-len[info.p];
		heap.push(Info(info.p,len[info.p])); 
	}
	printf("%lld\n",res);
	return 0;
}

