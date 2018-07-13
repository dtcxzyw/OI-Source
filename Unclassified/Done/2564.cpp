#include <cstdio>
#include <algorithm>
#include <climits>
int pcnt[60]={};
struct Info{
	int p,k;
	bool operator<(Info rhs) const{
		return p<rhs.p;
	}
} A[1000000];
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
int main(){
	int n,k,cnt=0;
	n=read();
	k=read();
	for(int i=0;i<k;++i){
		int siz=read();
		for(int j=0;j<siz;++j){
			A[cnt].p=read();
			A[cnt].k=i;
			++cnt;
		}
	}
	std::sort(A,A+n);
	cnt=0;
	int ans=INT_MAX;
	for(int l=0,r=-1;l<n;++l){
		while(cnt<k&&r+1<n){
			++r;
			if(++pcnt[A[r].k]==1)++cnt;
		}
		if(cnt==k)ans=std::min(ans,A[r].p-A[l].p);
		if(--pcnt[A[l].k]==0)--cnt;
	}
	printf("%d\n",ans);
	return 0;
}

