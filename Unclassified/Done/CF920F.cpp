#include <cstdio>
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
const int bsiz=1000100;
int prime[bsiz],fac[bsiz],d[bsiz];
bool flag[bsiz]={};
void pre(int maxv){
	fac[1]=1;
	int pcnt=0;
	for(int i=2;i<=maxv;++i){
		if(!flag[i]){
			prime[++pcnt]=i;
			fac[i]=2;
			d[i]=1;
		}
		for(int j=1;j<=pcnt && prime[j]*i<=maxv;++j){
			int val=prime[j]*i;
			flag[val]=true;
			if(i%prime[j]){
				fac[val]=fac[i]<<1;
				d[val]=1;
			}
			else{
				fac[val]=fac[i]/(d[i]+1)*(d[i]+2);
				d[val]=d[i]+1;
				break;
			}
		}
	}
}
const int size=300100;
long long sum[size<<2],maxv=0;
bool end[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r){
		sum[id]=read();
		if(sum[id]>maxv)
			maxv=sum[id];
		end[id]=sum[id]==fac[sum[id]];
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
		end[id]=end[id<<1]&end[id<<1|1];
	}
}
int nl,nr;
void modify(int l,int r,int id){
	if(!end[id]){
		if(l==r){
			sum[id]=fac[sum[id]];
			end[id]=sum[id]==fac[sum[id]];
		}
		else{
			int m=(l+r)>>1;
			if(nl<=m)modify(ls);
			if(m<nr)modify(rs);
			sum[id]=sum[id<<1]+sum[id<<1|1];
			end[id]=end[id<<1]&end[id<<1|1];
		}
	}
}
long long res;
void query(int l,int r,int id){
	if(nl<=l && r<=nr)res+=sum[id];
	else{
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
int main(){
	int n=read();
	int m=read();
	build(1,n,1);
	pre(maxv);
	for(int i=0;i<m;++i){
		int op=read();
		nl=read();
		nr=read();
		if(op==1)modify(1,n,1);
		else{
			res=0;
			query(1,n,1);
			printf("%lld\n",res);
		}
	}
	return 0;
}

