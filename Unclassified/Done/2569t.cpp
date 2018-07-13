#include <cstdio>
#include <cstring>
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
struct Deque{
	std::pair<int,long long> q[2010];
	int b,e;
	Deque():b(0),e(0){}
	void push(int i,long long v){
		if(b==e || q[e-1].second<v){
			q[e].first=i;
			q[e].second=v;
			++e;
		}
	}
	int size() const{
		return e-b;
	}
	void pop(int x){
		while(e-b>1 && q[b+1].first<=x)++b;
	}
	long long back() const{
		return q[e-1].second;
	}
	long long front() const{
		return q[b].second;
	}
} q[2010];
int maxv(int a,int b){
	return a>b?a:b;
}
int minv(int a,int b){
	return a<b?a:b;
}
void CAS(long long& a,long long b){
	if(a<b)a=b;
}
long long val[2010];
int main(){
	int t=read();
	int p=read();
	int w=read();
	q[0].push(0,0);
	for(int i=1;i<=t;++i){
		int ap=read();
		int bp=read();
		int as=read();
		int bs=read();
		for(int j=0;j<=p;++j)
			q[j].pop(i-w);
		for(int j=0;j<=p;++j){
			val[j]=-1LL<<60;
			for(int k=maxv(j-as,0);k<j;++k)if(q[k].size())
				CAS(val[j],q[k].front()-1LL*(j-k)*ap);
			for(int k=minv(j+bs,p);k>j;--k)if(q[k].size())
				CAS(val[j],q[k].front()+1LL*(k-j)*bp);
		}
		for(int j=0;j<=p;++j)
			if(val[j]>-1LL<<30)
				q[j].push(i,val[j]); 
	}
	long long ans=0;
	for(int i=0;i<=p;++i)
		if(q[i].size())
			CAS(ans,q[i].back());	
	printf("%lld\n",ans);
	return 0;
}

