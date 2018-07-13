#include <cstdio>
#include <string>
#include <algorithm>
#include <cctype>
const int size=50001;
std::string word[size],cw[size];
int maxv[size<<2|1]={},id[size],pos[size];
int cmpid(int lhs,int rhs){
	return pos[lhs]>pos[rhs]?lhs:rhs;
}
void update(int id){
	maxv[id]=cmpid(maxv[id<<1],maxv[id<<1|1]);
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)maxv[id]=l;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return maxv[id];
	else{
		int m=(l+r)>>1,v=0;
		if(nl<=m)v=cmpid(v,query(ls,nl,nr));
		if(m<nr)v=cmpid(v,query(rs,nl,nr));
		return v;
	}
}
void read(int i){
	int c;
	do c=getchar();
	while(!isalpha(c));
	while(isalpha(c)){
		word[i].push_back(c); 
		cw[i].push_back(tolower(c));
		c=getchar();
	}
}
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
bool cmp(int lhs,int rhs){
	return cw[lhs]<cw[rhs];
}
int main(){
	int n,m;
	n=read();
	m=read();
	for(int i=1;i<=n;++i){
		id[i]=i;
		read(i);
	}
	std::stable_sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;++i)
		pos[id[i]]=i;
	build(1,n,1);
	int l,r;
	for(int i=0;i<m;++i){
		l=read();
		r=read();
		puts(word[query(1,n,1,l,r)].c_str());
	}
	return 0;
}

