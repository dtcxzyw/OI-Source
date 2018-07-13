#include <cstdio>
#include <queue>
bool flag[200000]={};
int n;
struct Info{
	int p,w;
	Info(int id,int v):p(id),w(v){}
	operator bool() const{
		return !(flag[(p+1)%n]||flag[(p-1+n)%n]);
	}
	bool operator<(Info rhs) const{
		return w<rhs.w;
	}
};
int w[200000];
int main(){
	int m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		scanf("%d",&w[i]);
	std::priority_queue<Info> heap;
	for(int i=0;i<n;++i)
		heap.push(Info(i,w[i]));
	int sum=0,cnt=0;
	while(cnt<m && heap.size()){
		Info top=heap.top();
		heap.pop();
		if(top){
			sum+=top.w;
			flag[top.p]=true;
			++cnt;
		}
	}
	if(cnt!=m) puts("Error!");
	else printf("%d\n",sum);
	return 0;
}

