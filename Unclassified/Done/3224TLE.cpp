#include <cstdio>
#include <vector>
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
int getOp(){
	int c;
	do c=getchar();
	while(c!='B'&&c!='Q');
	return c;
}
const int size=250100;
struct Info{
	int id,key;
	Info(int i,int k):id(i),key(k){}
	bool operator<(Info rhs) const{
		return key<rhs.key;
	}
};
typedef std::vector<Info> OrderedList;
OrderedList list[size];
int fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void mergeList(OrderedList& res,const OrderedList& lhs,const OrderedList& rhs){
	res.reserve(lhs.size()+rhs.size());
	int lp=0,rp=0;
	while(lp<lhs.size() && rp<rhs.size()){
		if(lhs[lp]<rhs[rp])res.push_back(lhs[lp++]);
		else res.push_back(rhs[rp++]);
	}
	while(lp<lhs.size())res.push_back(lhs[lp++]);
	while(rp<rhs.size())res.push_back(rhs[rp++]);
}
void clear(OrderedList& list){
	OrderedList tmp;
	tmp.swap(list);
}
void merge(int& cnt,int u,int v){
	u=find(u),v=find(v);
	if(u!=v){
		int p=++cnt;
		mergeList(list[p],list[u],list[v]);
		clear(list[u]);
		clear(list[v]);
		fa[u]=fa[v]=fa[p]=p;
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		fa[i]=i;
		list[i].push_back(Info(i,read())); 
	}
	for(int i=0;i<m;++i)
		merge(n,read(),read());
	int q=read();
	for(int i=0;i<q;++i)
		if(getOp()=='B')merge(n,read(),read());
		else{
			int u=find(read());
			int x=read()-1;
			if(x<list[u].size())printf("%d\n",list[u][x].id);
			else puts("-1");
		}
	return 0;
}

