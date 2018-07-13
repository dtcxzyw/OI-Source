#include <cstdio>
#include <queue>
#include <algorithm>
int read(){
	int res=0,c;
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
const int size=500005;
int sum[size],st[20][size],lg[size];
int choose(int a,int b){
	return sum[a]>sum[b]?a:b;
}
void pre(int n){
	lg[1]=0;
	for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i)
		st[0][i]=i;
	for(int i=1;i<20;++i){
		int end=n-(1<<i)+1,off=1<<(i-1);
		for(int j=1;j<=end;++j)
			st[i][j]=choose(st[i-1][j],st[i-1][j+off]);
	}
}
int query(int l,int r){
	int p=lg[r-l+1];
	return choose(st[p][l],st[p][r-(1<<p)+1]);
}
struct Node{
	int l,r,b,e,val;
	Node(int l,int r,int b):l(l),r(r),b(b),e(query(l,r)),val(sum[e]-sum[b-1]){}
	bool operator<(const Node& rhs) const{
		return val<rhs.val;
	}
};
int main(){
	int n=read();
	int k=read();
	int l=read();
	int r=read();
	sum[0]=0;
	for(int i=1;i<=n;++i)sum[i]=sum[i-1]+read();
	pre(n);
	
	std::priority_queue<Node> heap;
	int end=n-l+1;
	for(int i=1;i<=end;++i){
		int cl=i+l-1,cr=std::min(i+r-1,n);
		heap.push(Node(cl,cr,i));
	}
	long long res=0;
	while(k--){
		Node top=heap.top();
		heap.pop();
		res+=top.val;
		if(top.e>top.l)heap.push(Node(top.l,top.e-1,top.b));
		if(top.e<top.r)heap.push(Node(top.e+1,top.r,top.b));
	}
	printf("%lld\n",res);
	return 0;
}

