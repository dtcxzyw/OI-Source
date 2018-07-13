#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=1005,len=5005,mod=1000000007;
char buf[len];
int end;
struct Bitset{
	unsigned long long val[(size>>6)+1];
	void set(int p){
		val[p>>6]|=1ULL<<(p&63);
	}
	bool operator<(const Bitset& rhs) const{
		for(int i=end-1;i>=0;--i)
			if(val[i]!=rhs.val[i])
				return val[i]<rhs.val[i];
		return false;
	}
} bit[len];
int id[len],val[len],powv[len];
bool cmp(int a,int b){
	return bit[a]<bit[b];
}
int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	end=(n>>6)+1;
	powv[0]=1;
	for(int i=1;i<len;++i)
		powv[i]=(powv[i-1]<<1)%mod;
	for(int i=0;i<n;++i){
		scanf("%s",buf);
		for(int j=0;j<m;++j){
			int x=buf[j]=='1';
			if(x){
				bit[j].set(i);
				val[j]=(val[j]+powv[i])%mod;
			}	
		}
	}
	for(int i=0;i<m;++i)id[i]=i;
	std::sort(id,id+m,cmp);
	for(int i=0;i<q;++i){
		scanf("%s",buf);
		int l=-1,r=m;
		for(int j=m-1;j>=0;--j)
			if(buf[id[j]]=='0'){
				l=j;
				break;
			}
		for(int j=0;j<m;++j)
			if(buf[id[j]]=='1'){
				r=j;
				break;
			}
		if(l<r){
			int a=r==m?powv[n]:val[id[r]];
			int b=l==-1?0:val[id[l]];
			printf("%d\n",((a-b)%mod+mod)%mod);
		}
		else puts("0");
	}
	return 0;
}

