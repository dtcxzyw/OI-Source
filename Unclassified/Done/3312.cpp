#include <cstdio>
#include <algorithm>
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
const int size=100100;
int prime[size],pcnt=0,mu[size],minp[size]={},t1[size],t2[size];
struct F{
	int v,i;
	bool operator<(F rhs) const{
		return v<rhs.v;
	}
} f[size];
void pre(int n){
	f[1].v=f[1].i=mu[1]=1;
	for(int i=2;i<=n;++i){
		f[i].i=i;
		if(!minp[i]){
			minp[i]=prime[++pcnt]=i;
			t1[i]=1+i;
			t2[i]=i;
			mu[i]=-1;
			f[i].v=i+1;
		}
		for(int j=1;j<=pcnt && i*prime[j]<=n;++j){
			int k=i*prime[j];
			minp[k]=prime[j];
			if(i%prime[j]){
				mu[k]=-mu[i];
				t1[k]=1+prime[j];
				t2[k]=prime[j];	
				f[k].v=f[i].v*f[prime[j]].v;
			}else{
				mu[k]=0;
				t2[k]=t2[i]*prime[j];
				t1[k]=t1[i]+t2[k];
				f[k].v=f[i].v/t1[i]*t1[k];
				break;
			}
		}
	}
}
struct Query{
	int n,m,a,id;
	bool operator<(const Query& rhs) const{
		return a<rhs.a;
	}
} Q[size];
int ans[size]={},A[size]={};
void add(int i,int siz,int v){
	while(i<=siz){
		A[i]+=v;
		i+=i&-i;
	}
}
int query(int i){
	int res=0;
	while(i){
		res+=A[i];
		i-=i&-i;
	}
	return res;
}
int maxv(int a,int b){
	return a>b?a:b;
}
int minv(int a,int b){
    return a<b?a:b;
}
void foo(int x){
	int end=minv(Q[x].n,Q[x].m);
	for(int i=1,nxt;i<=end;i=nxt+1){
		nxt=minv(Q[x].n/(Q[x].n/i),Q[x].m/(Q[x].m/i));
		ans[Q[x].id]+=(Q[x].n/i)*(Q[x].m/i)*(query(nxt)-query(i-1));
	}
}
int main(){
	int q=read(),maxs=0;
	for(int i=0;i<q;++i){
		Q[i].id=i;
		Q[i].n=read();
		Q[i].m=read();
		maxs=maxv(maxs,maxv(Q[i].n,Q[i].m));
		Q[i].a=read();
	}
	pre(maxs);
	std::sort(Q,Q+q);
	std::sort(f+1,f+maxs+1);
	for(int i=0,c=1;i<q;++i){
		while(c<=maxs&&f[c].v<=Q[i].a){
			for(int j=f[c].i,d=1;j<=maxs;j+=f[c].i,++d)
				add(j,maxs,f[c].v*mu[d]);
			++c;
		}
		foo(i);
	}
	for(int i=0;i<q;++i)
		printf("%d\n",ans[i]&0x7fffffff);
	return 0;	
}

