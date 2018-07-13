#include <cstdio>
#include <queue>
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
const int asiz=2005;
struct Edge{
	int to,next;
} E[10005];
int last[asiz]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int t[asiz],d[asiz]={},tmp[asiz];
struct Info{
	int u,t;
	Info(){}
	Info(int u,int t):u(u),t(t){}
	bool operator<(Info rhs) const{
		return t<rhs.t;
	}
};
class FixedSizeArray{
private:
	Info A[asiz];
	int siz;
public:
	typedef Info value_type;
	typedef Info reference;
	typedef Info const_reference;
	typedef int size_type;
	FixedSizeArray():siz(0){}
	Info front() const{
		return A[0];
	}
	void push_back(Info x){
		A[siz++]=x;
	}
	void pop_back(){
		--siz;
	}
	int size() const{
		return siz;
	}
	bool empty() const{
		return siz==0;
	}
	Info* begin(){
		return A;
	}
	Info* end(){
		return A+siz;
	}
};
int foo(int x,int n){
	std::priority_queue<Info,FixedSizeArray> q;
	memcpy(tmp,d,sizeof(d));
	tmp[x]=-1;
	for(int i=1;i<=n;++i)
		if(!tmp[i])q.push(Info(i,t[i]));
	for(int i=n;i>=1;--i){
		if(q.empty()||q.top().t<i)return i;
		int u=q.top().u;
		q.pop();
		for(int j=last[u];j;j=E[j].next){
			int v=E[j].to;
			if(--tmp[v]==0)q.push(Info(v,t[v]));
		}
	}
}
int order[asiz];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)
		t[i]=read();
	for(int i=0;i<m;++i){
		int a=read();
		int b=read();
		addEdge(b,a);
		++d[a];
	}
	std::priority_queue<Info> q;
	memcpy(tmp,d,sizeof(d));
	for(int i=1;i<=n;++i)
		if(!tmp[i])q.push(Info(i,t[i]));
	for(int i=n;i>=1;--i){
		int u=q.top().u;
		q.pop();
		order[i]=u;
		for(int j=last[u];j;j=E[j].next){
			int v=E[j].to;
			if(--tmp[v]==0)q.push(Info(v,t[v]));
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d ",order[i]);
	puts("");
	for(int i=1;i<=n;++i)
		printf("%d ",foo(i,n));
	puts("");
	return 0;
}

