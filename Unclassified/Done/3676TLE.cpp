#include <cstdio>
typedef long long Int64;
int read(){
    int res=0,c;
    bool flag=0;
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
Int64 sqr(Int64 x){
	return x*x;
}
const int size=200100;
struct Edge{
    int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
int p[size],d[size],siz[size],son[size]={},B[size];
void buildTree(int u){
    siz[u]=1;
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(p[u]!=v){
            p[v]=u;
            d[v]=d[u]+1;
            buildTree(v);
            siz[u]+=siz[v];
            B[u]+=B[v];
            if(siz[son[u]]<siz[v])
            	son[u]=v;
        }
    }
}
int top[size],id[size]={},pid[size],icnt=0;
void buildChain(int u){
	id[u]=++icnt;
	pid[icnt]=u;
	if(son[u]){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!id[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
Int64 sum1[size<<2],sum2[size<<2],lazy[size<<2]={};
void update(int id){
	sum1[id]=sum1[id<<1]+sum1[id<<1|1];
	sum2[id]=sum2[id<<1]+sum2[id<<1|1];
}
void build(int l,int r,int id){
	if(l==r){
		int p=pid[l];
		sum1[id]=B[p];
		sum2[id]=sqr(B[p]);
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
void color(int l,int r,int id,Int64 val){
	Int64 add=val*(r-l+1);
	sum2[id]+=val*(2*sum1[id]+add);
	sum1[id]+=add;
	lazy[id]+=val;
}
void push(int l,int r,int id){
	if(lazy[id]!=0){
		int m=(l+r)>>1;
		color(ls,lazy[id]);
		color(rs,lazy[id]);
		lazy[id]=0;
	}
}
int nl,nr,val;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,val);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		update(id);
	}
}
Int64 res;
template<Int64* sum>
void query(int l,int r,int id){
	if(nl<=l && r<=nr)res+=sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)query<sum>(ls);
		if(m<nr)query<sum>(rs);
	}
}
int n;
void modifyChain(int u){
	while(u){
		nl=id[top[u]];
		nr=id[u];
		modify(1,n,1);
		u=p[top[u]];
	}
}
Int64 queryChain(int u){
	res=0;
	while(u){
		nl=id[top[u]];
		nr=id[u];
		query<sum2>(1,n,1);
		u=p[top[u]];
	}
	return res;
}
Int64 queryRoot(int u){
	res=0,nl=nr=id[u];
	query<sum1>(1,n,1);
	return res;
}
int A[size];
int main(){
    n=read();
    int m=read();
    for(int i=1;i<n;++i){
        int u=read();
        int v=read();
        addEdge(u,v);
        addEdge(v,u);
    }
    
    Int64 sum=0;
    for(int i=1;i<=n;++i)sum+=A[i]=B[i]=read();
    
    siz[0]=0,p[1]=0;
    buildTree(1);
    top[1]=1;
    buildChain(1);
    
    build(1,n,1);
    
	for(int i=0;i<m;++i)
    	if(read()==1){
    		int u=read();
    		int v=read();
    		val=v-A[u];
    		modifyChain(u);
    		sum+=val;
    		A[u]=v;
    	}
    	else{
    		int u=read();
    		Int64 sumRoot=sum2[1]-sum*sum1[1];
    		Int64 sumU=sum1[1],now=sum;
			while(u){
				Int64 old=queryRoot(u);
				sumU+=now-old;
				now=sum-old;
    			u=p[u];
    		}
			printf("%lld\n",sumRoot+sum*sumU);
    	}
    return 0;
}

