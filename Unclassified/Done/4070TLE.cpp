#include <cstdio>
#include <vector>
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
const int size=100100,mask=(1<<20)-1;
long long base[size]={},cnt=0;
std::vector<long long> buc[1<<20];
void insert(long long x){
	long long base=x&mask;
	for(int i=0;i<buc[base].size();++i)
		if(x==buc[base][i])
			return;
	buc[base].push_back(x);
	++cnt;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		int x=read();
		for(int j=i;j>=1;--j){
			base[j]=base[j-1]*131313+x;
			insert(base[j]); 
		}
		printf("%d\n",cnt);
	}
	return 0;
}

