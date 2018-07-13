#include <cstdio>
#include <deque>
#include <cstring>
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
const int size=100100;
int s[size],siz[size<<2],time,leaf[size];
std::deque<int> food[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	siz[id]=0;
	food[id].clear();
	if(l==r)leaf[l]=id;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
	}
}
void update(int id){
	while(food[id].size() && food[id].front()<=time)++siz[id],food[id].pop_front();
}
int find(int l,int r,int id){
	if(l==r)return l;
	else{
		int m=(l+r)>>1;
		update(id<<1);
		if(siz[id<<1])return find(ls);
		return find(rs);
	}
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr){
		update(id);
		return siz[id];
	}else{
		int m=(l+r)>>1,res=0;
		if(nl<=m)res+=query(ls,nl,nr);
		if(m<nr)res+=query(rs,nl,nr);
		return res;
	}
}
void erase(int id){
	int p=leaf[id];
	while(p){
		update(p);
		--siz[p];
		p>>=1;
	}
}
void foo(){
	int n=read();
	build(1,n,1);
	for(int i=1;i<=n;++i)s[i]=read();
	int q=read();
	for(int i=0;i<q;++i){
		time=read();
		int op=read();
		switch(op){
			case 0:{
				int id=read();
				int end=time+s[id];
				int p=leaf[id];
				while(p){
					food[p].push_back(end);
					p>>=1;
				}
			}break;
			case 1:{
				update(1);
				if(siz[1]){
					int k=find(1,n,1);
					erase(k);
					printf("%d\n",k);
				}
				else puts("Yazid is angry.");
			}break;
			case 2:{
				int id=read();
				if(siz[leaf[id]] || food[leaf[id]].size()){
					update(leaf[id]);
					if(siz[leaf[id]]){
						puts("Succeeded!");
						erase(id);
					}
					else printf("%d\n",food[leaf[id]].front()-time);
				}
				else puts("YJQQQAQ is angry.");
			}break;
			case 3:{
				int l=read();
				int r=read();
				printf("%d\n",query(1,n,1,l,r));
			}break;
		}
	}
}
int main(){
	int t=read();
	while(t--)foo();
	return 0;
}

