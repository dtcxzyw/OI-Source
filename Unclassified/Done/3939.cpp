#include <cstdio>
#include <vector>
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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
std::vector<int> pos[300001];
int col[300001];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		col[i]=read();
		pos[col[i]].push_back(i); 
	}
	int x,l,r;
	for(int i=0;i<m;++i){
		typedef std::vector<int>::iterator iter_t;
		if(read()==1){
			l=read();
			r=read();
			x=read();
			iter_t a=std::lower_bound(pos[x].begin(),pos[x].end(),l);
			iter_t b=std::lower_bound(pos[x].begin(),pos[x].end(),r+1);
			print(b-a);
		}
		else{
			x=read();
			if(col[x]!=col[x+1]){
				iter_t a=std::lower_bound(pos[col[x]].begin(),pos[col[x]].end(),x);
				iter_t b=std::lower_bound(pos[col[x+1]].begin(),pos[col[x+1]].end(),x+1);
				std::swap(*a,*b);
				std::swap(col[x],col[x+1]);
			}
		}
	}
	return 0;
}

