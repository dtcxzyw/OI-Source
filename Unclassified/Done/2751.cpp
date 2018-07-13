#include <cstdio>
#include <queue>
struct Info{
	int end,t;
	bool operator<(Info rhs) const{
		return end>rhs.end;
	}
};
int t[1001];
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	std::priority_queue<Info> qa,qb;
	for(int i=0;i<a;++i){
		Info info;
		scanf("%d",&info.t);
		info.end=info.t;
		qa.push(info); 
	}
	for(int i=1;i<=n;++i){
		Info x=qa.top();
		qa.pop();
		t[i]=x.end;
		x.end+=x.t;
		qa.push(x); 
	}
	int aans=t[n];
	for(int i=0;i<b;++i){
		Info info;
		scanf("%d",&info.t);
		info.end=info.t;
		qb.push(info); 
	}
	int bans=0;
	for(int i=n;i>=1;--i){
		Info x=qb.top();
		qb.pop();
		t[i]+=x.end;
		if(t[i]>bans)bans=t[i];
		x.end+=x.t;
		qb.push(x); 
	}
	printf("%d %d\n",aans,bans);
	return 0;
}

