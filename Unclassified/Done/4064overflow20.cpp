#include <cstdio>
#include <vector>
#include <algorithm>
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
const int size=200100;
double A[size];
int n;
void add(int i,double w){
	while(i<=n){
		A[i]+=w;
		i+=i&-i;
	}
}
double query(int i){
	double res=0.0;
	while(i){
		res+=A[i];
		i-=i&-i;
	}
	return res;
}
double query(int l,int r){
	return query(r)-query(l-1);
}
long long val[size];
int id[size];
bool cmp(int a,int b){
	return val[a]>val[b];
}
std::vector<int> range[size];
void foo(){
	n=read();
	int m=read();
	int k=read();
	int a=read();
	for(int i=1;i<=n;++i)range[i].clear();
	for(int i=1;i<=n;++i)val[i]=read();
	for(int i=1;i<=n;++i)id[i]=i;
	for(int i=0;i<m;++i){
		int l=read();
		int r=read();
		range[l].push_back(r); 
	}
	for(int i=1;i<=n;++i)
		std::sort(range[i].begin(),range[i].end());
	for(int i=0;i<k;++i){
		memset(A,0,sizeof(A));
		std::sort(id+1,id+n+1,cmp);
		double cw=1.0;
		for(int j=1;j<=n;++j){
			add(id[j],cw);
			if(val[id[j]]!=val[id[j+1]])cw*=n;
		}
		int maxl=-1;
		double w=0.0;
		for(int l=1;l<=n;++l)
			if(range[l].size()){
				int r=range[l].back();
				double cw=query(l,r);
				if(cw>w)maxl=l,w=cw;
			}
		int nl=maxl,nr=range[nl].back();
		range[nl].pop_back();
		for(int j=nl;j<=nr;++j)
			val[j]+=a;
	}
	printf("%lld\n",*std::min_element(val+1,val+n+1));
}
int main(){
	int t=read();
	while(t--)foo();
	return 0;
}

