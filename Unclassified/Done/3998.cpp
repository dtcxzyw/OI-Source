#include <cstdio>
#include <set>
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
int getOp(){
	int c;
	do c=getchar();
	while(c!='!' && c!='+' && c!='-');
	return c;
}
void print(int x){
	if(x>=10)print(x/10);
	putchar('0'+x%10);
}
const int size=200100;
int sum[size]={},cnt[size]={};
std::set<int> to[size];
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int op=getOp();
		int x=read();
		if(op=='!')++cnt[x];
		else{
			int y=read();
			if(op=='+'){
				to[x].insert(y);
				sum[y]-=cnt[x];
				to[y].insert(x);
				sum[x]-=cnt[y];
			}
			else{
				to[x].erase(y);
				sum[y]+=cnt[x];
				to[y].erase(x);
				sum[x]+=cnt[y];
			}
		}
	}
	for(int i=1;i<=n;++i)
		for(std::set<int>::iterator it=to[i].begin();it!=to[i].end();++it)
			sum[*it]+=cnt[i];
	for(int i=1;i<=n;++i){
		print(sum[i]);
		if(i!=n)putchar(' ');	
	}
	return 0;
}

