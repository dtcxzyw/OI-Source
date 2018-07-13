#include <cstdio>
#include <algorithm>
#include <cstring>
int read(){
	int res=0,c;
	bool flag=false;
	do{ 
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int getOp(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c;
}
const int asiz=50010,size=asiz<<2,mod=19940417;
long long sum[size][21];
int lazy[size]={},siz[size],rsiz[size];
bool rev[size]={};
void update(int id){
	for(int i=1;i<=siz[id];++i){
		int beg=std::max(i-siz[id<<1|1],0);
		int end=std::min(siz[id<<1],i);
		long long res=0;
		for(int j=beg;j<=end;++j)
			res+=sum[id<<1][j]*sum[id<<1|1][i-j]; 
		sum[id][i]=res%mod;
	}
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	sum[id][0]=1;
	rsiz[id]=r-l+1;
	siz[id]=std::min(rsiz[id],20);
	if(l==r)sum[id][1]=(read()%mod+mod)%mod;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
void colRev(int id){
	lazy[id]=-lazy[id];
	rev[id]=!rev[id];
	for(int i=1;i<=siz[id];i+=2)
		sum[id][i]=-sum[id][i];
}
long long C[asiz][21]={};
void colAdd(int id,int val){
	lazy[id]=(lazy[id]+val)%mod;
	for(int i=siz[id];i>=1;--i){
		long long res=0;
		for(int j=0;j<=i;++j)
			res=(res*val+sum[id][j]*C[rsiz[id]-j][i-j])%mod;
		sum[id][i]=res;
	}
}
void push(int id){
	if(rev[id]){
		colRev(id<<1);
		colRev(id<<1|1);
		rev[id]=false;
	}
	if(lazy[id]){
		colAdd(id<<1,lazy[id]);
		colAdd(id<<1|1,lazy[id]);
		lazy[id]=0;
	}
}
int nl,nr,val;
void add(int l,int r,int id){
	if(nl<=l && r<=nr)colAdd(id,val);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)add(ls);
		if(m<nr)add(rs);
		update(id);
	}
}
void reverse(int l,int r,int id){
	if(nl<=l && r<=nr)colRev(id);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)reverse(ls);
		if(m<nr)reverse(rs);
		update(id);
	}
}
long long res[21];
int csiz;
void merge(int id){
	int nsiz=std::min(csiz+siz[id],val);
	for(int i=nsiz;i>=1;--i){
		int beg=std::max(i-siz[id],0);
		int end=std::min(csiz,i);
		long long now=0;
		for(int j=beg;j<=end;++j)
			now+=res[j]*sum[id][i-j]; 
		res[i]=now%mod;
	}
	csiz=nsiz;
}
void query(int l,int r,int id){
	if(nl<=l && r<=nr)merge(id);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
void pre(int n){
	C[0][0]=1;
	for(int i=1;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=20;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int main(){
	int n=read();
	int q=read();
	pre(n);
	build(1,n,1);
	for(int i=0;i<q;++i){
		int op=getOp();
		nl=read();
		nr=read();
		if(op!='R')val=read();
		switch(op){
			case 'I':{
				add(1,n,1);
				break;
			}
			case 'R':{
				reverse(1,n,1);
				break;
			}
			case 'Q':{
				csiz=0;
				memset(res+1,0,sizeof(int)*val);
				res[0]=1;
				query(1,n,1);
				printf("%lld\n",(res[val]+mod)%mod);
				break;
			}
		}
	}
	return 0;
}

