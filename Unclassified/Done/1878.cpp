#include <cstdio>
#include <queue>
#include <cmath>
#include <cstring>
const int size=200001;
int prev[size]={},next[size]={},w[size];
char buf[size+10],in[size];
struct Info{
	int l,r,w;
	Info(){}
	Info(int L,int R,int c):l(L),r(R),w(c){}
	bool operator<(Info rhs) const{
		return w==rhs.w?l>rhs.l:w>rhs.w;
	}
};
Info q[size];
int main(){
	int n;
	scanf("%d%s",&n,buf+1);
	for(int i=1;i<=n;++i){
		if(i>1)prev[i]=i-1;
		if(i<n)next[i]=i+1;
		scanf("%d",&w[i]);
	}
	
	std::priority_queue<Info> heap; 
	for(int i=1;i<n;++i)
		if(buf[i]!=buf[i+1])
			heap.push(Info(i,i+1,std::abs(w[i]-w[i+1])));
	memset(in,0xff,sizeof(in));
	int cnt=0;
	while(heap.size()){
		Info top=heap.top();
		heap.pop();
		if(in[top.l]&&in[top.r]){
			in[top.l]=in[top.r]=false;
			q[cnt++]=top;
			int l=prev[top.l],r=next[top.r];
			prev[r]=l,next[l]=r;
			if(l && r && buf[l]!=buf[r])
				heap.push(Info(l,r,std::abs(w[l]-w[r])));
		}
	}
	printf("%d\n",cnt);
	for(int i=0;i<cnt;++i)
		printf("%d %d\n",q[i].l,q[i].r);
	return 0;
}

