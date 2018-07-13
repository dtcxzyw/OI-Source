#include <cstdio>
#include <algorithm>
#include <set>
const int size=1000000;
int ID[size],pos[size],t[size];
bool flag[size]={};
int cnt[size]={};
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
struct Cmp{
	bool operator()(int a,int b) const{
		return cnt[a]==cnt[b]?t[a]<t[b]:cnt[a]<cnt[b];
	}
};
std::set<int,Cmp> q;
int main(){
	int n,m,ans=0;
	n=read();
	m=read();
	for(int i=0;i<m;++i)pos[i]=ID[i]=read();
	std::sort(pos,pos+m);
	int siz=std::unique(pos,pos+m)-pos;
	for(int i=0;i<m;++i){
		int p=std::lower_bound(pos,pos+siz,ID[i])-pos;
		if(flag[p])q.erase(p),++ans;
		else{
			if(q.size()==n){
				int u=*q.begin();
				q.erase(q.begin());
				flag[u]=false,cnt[u]=0;
			}
			flag[p]=true;
		}
		++cnt[p],t[p]=i;
		q.insert(p); 
	}
	printf("%d\n",ans);
	return 0;
}

