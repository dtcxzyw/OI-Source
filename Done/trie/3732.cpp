#include <cstdio>
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
const int size=100005,maxl=40;
struct Node{
	int timeStamp,c[2];
} T[size*maxl];
int cnt=0,pos[maxl+5]={};
char buf[size];
void CAS(int& a,int b){
	if(a<b)a=b;
}
void insert(int beg,int end){
	int p=0;
	for(int i=beg;i<=end;++i){
		int& cur=T[p].c[buf[i]];
		if(cur)CAS(pos[i-beg+1],T[cur].timeStamp);
		else cur=++cnt;
		T[cur].timeStamp=beg;
		p=cur;
	}
}
struct Query{
	int l,r,id;
	bool operator<(const Query& rhs) const{
		return r<rhs.r;
	}
} Q[size];
int ans[size];
int main(){
	int n=read();
	int q=read();
	scanf("%s",buf+1);
	for(int i=1;i<=n;++i)buf[i]-='0';
	for(int i=0;i<q;++i){
		Q[i].l=read();
		Q[i].r=read();
		Q[i].id=i;
	}
	std::sort(Q,Q+q);
	int r=0;
	for(int i=0;i<q;++i){
		while(r!=Q[i].r){
			++r;
			insert(r,std::min(r+maxl-1,n));
		}
		int res=0;
		for(int j=1;j<=maxl && pos[j]>=Q[i].l;++j)
			res+=pos[j]-Q[i].l+1;
		ans[Q[i].id]=res;
	}
	for(int i=0;i<q;++i)
		printf("%d\n",ans[i]);
	return 0;
}

