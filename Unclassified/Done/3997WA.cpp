#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
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
const int size=100100;
struct Range{
	int r,b,e;
} R[size];
int P[2*size];
std::vector<int> add[2*size],sub[2*size];
int getPos(int x,int cnt){
	return std::lower_bound(P,P+cnt,x)-P;
}
int main(){
	int n=read();
	int m=read();
	int k=read();
	int cnt=0;
	for(int i=0;i<n;++i){
		R[i].r=read();
		P[cnt++]=R[i].b=read();
		P[cnt++]=R[i].e=read();
	}
	std::sort(P,P+cnt);
	cnt=std::unique(P,P+cnt)-P;
	for(int i=0;i<n;++i){
		add[getPos(R[i].b,cnt)].push_back(R[i].r);
		sub[getPos(R[i].e,cnt)].push_back(R[i].r);
	}
	typedef std::multiset<int> Set;
	Set cur;
	long long ans=0;
	for(int i=0;i<cnt-1;++i){
		cur.insert(add[i].begin(),add[i].end());
		for(int j=0;j<sub[i].size();++j)
			cur.erase(cur.find(sub[i][j]));
		/*
		printf("[%d,%d):\n",P[i],P[i+1]);
		for(Set::iterator it=cur.begin();it!=cur.end();++it)
			printf("%d\n",*it);
		*/
		if(cur.size()>=k){
			Set::reverse_iterator it=cur.rbegin();
			std::advance(it,k-1);
			long long r=*it,rad=P[i+1]-P[i];
			ans+=r*r*rad;
			//printf("r=%I64d rad=%I64d\n",r,rad);
		}
	}
	printf("%lld\n",ans);
	return 0;
}

