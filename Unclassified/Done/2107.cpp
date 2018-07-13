#include <cstdio>
#include <queue>
#include <algorithm>
struct Info{
    long long x,t;
    bool operator<(const Info& rhs) const{
        return x<rhs.x;
    }
} info[100000];
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
int main(){
    long long n,m;
    n=read();
    m=read();
    long long x,t;
    for(int i=0;i<n;++i){
        info[i].x=read();
        info[i].t=read();
    }
    std::sort(info,info+n);
    std::priority_queue<int> heap; 
    int ans=0;
    long long tot=0;
	for(int i=0;i<n;++i){
		long long maxt=m-info[i].x;
		if(maxt<0)break;
		tot+=info[i].t;
		heap.push(info[i].t);
		while(tot>maxt){
			tot-=heap.top();
			heap.pop();
		}
		ans=std::max(ans,static_cast<int>(heap.size()));
	}
    printf("%d\n",ans);
    return 0;
}

