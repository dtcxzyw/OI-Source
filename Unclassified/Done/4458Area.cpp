#include <cstdio>
#include <algorithm>
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
const int size=100005,mod=1000000007;
const long long inv2=500000004;
struct Block{
	int bx,ex,by,ey,siz;
    int sum[size<<2],lazy[size<<2][3],weight1[size<<2],weight2[size<<2];
    Block(){
        memset(sum,0,sizeof(sum));
        memset(lazy,0,sizeof(lazy));
    }
    #define ls l,m,id<<1
    #define rs m+1,r,id<<1|1
    void pre(int l,int r,int id){
    	if(l==r){
    		weight1[id]=l;
    		weight2[id]=static_cast<long long>(l)*l%mod;
    	}
    	else{
    		int m=(l+r)>>1;
    		pre(ls);
    		pre(rs);
    		weight1[id]=(weight1[id<<1]+weight1[id<<1|1])%mod;
    		weight2[id]=(weight2[id<<1]+weight2[id<<1|1])%mod;
    	}
    }
	void color0(int l,int r,int id,int val){
    	sum[id]=(sum[id]+static_cast<long long>(r-l+1)*val)%mod;
		lazy[id][0]=(lazy[id][0]+val)%mod;
    }
    void color1(int l,int r,int id,int val){
    	sum[id]=(sum[id]+static_cast<long long>(weight1[id])*val)%mod;
		lazy[id][1]=(lazy[id][1]+val)%mod;
	}
	void color2(int l,int r,int id,int val){
		sum[id]=(sum[id]+static_cast<long long>(weight2[id])*val)%mod;
		lazy[id][2]=(lazy[id][2]+val)%mod;
    }
    void push(int l,int r,int m,int id){
		if(lazy[id][0]){
			color0(ls,lazy[id][0]);
			color0(rs,lazy[id][0]);
			lazy[id][0]=0;
		}
		if(lazy[id][1]){
			color1(ls,lazy[id][1]);
			color1(rs,lazy[id][1]);
			lazy[id][1]=0;
		}
		if(lazy[id][2]){
			color2(ls,lazy[id][2]);
			color2(rs,lazy[id][2]);
			lazy[id][2]=0;
		}
    }
    int query(int l,int r,int id,int nl,int nr){
        if(nl<=l && r<=nr)return sum[id];
        else{
            int m=(l+r)>>1;
            push(l,r,m,id);
            int res=0;
            if(nl<=m)res+=query(ls,nl,nr);
            if(m<nr)res+=query(rs,nl,nr);
            return res%mod;
        }
    }
    void modify0(int l,int r,int id,int p,int val){
    	if(p<=l)color0(l,r,id,val);
		else{
			int m=(l+r)>>1;
			push(l,r,m,id);
			if(p<=m)modify0(ls,p,val);
			modify0(rs,p,val);
			sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
		}
	}
    void modify1(int l,int r,int id,int p,int val){
    	if(r<=p)color1(l,r,id,val);
		else{
			int m=(l+r)>>1;
			push(l,r,m,id);
			modify1(ls,p,val);
			if(m<p)modify1(rs,p,val);
			sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
		}
	}
	void modify2(int l,int r,int id,int p,int val){
		if(r<=p)color2(l,r,id,val);
		else{
			int m=(l+r)>>1;
			push(l,r,m,id);
			modify2(ls,p,val);
			if(m<p)modify2(rs,p,val);
			sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
		}
	}
    void doModifyImpl(int p,int val){
    	modify1(1,siz,1,p,val*(p+1-inv2)%mod);
    	modify2(1,siz,1,p,-val*inv2%mod);
    	if(p+1<=ey-by+1)modify0(1,siz,1,p+1,(static_cast<long long>(p)*(p+1)>>1)%mod*val%mod);
	}
    void doModify(int l,int r,int val){
        doModifyImpl(r,val);
    	if(l-1)doModifyImpl(l-1,-val);
	}
    int doQuery(int l,int r){
        return query(1,siz,1,l,r);
    }
} T[2][2];
void doModify(int n,int l,int r,int val){
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            int ibx=std::max(l,T[i][j].bx);
            int iex=std::min(r,T[i][j].ex);
            if(ibx<=iex)
                T[i][j].doModify(i?n-iex+1:ibx,i?n-ibx+1:iex,val);
        }
    }
}
int doQuery(int n,int l,int r){
    int res=0;
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            int iby=std::max(l,T[i][j].by);
            int iey=std::min(r,T[i][j].ey);
            if(iby<=iey)
                res=(res+T[i][j].doQuery(j?n-iey+1:iby,j?n-iby+1:iey))%mod;
        }
    }
    return (res+mod)%mod;
}
int main(){
    int n=read();
    int mid=(n+1)>>1;
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j){
            T[i][j].bx=(i?mid+1:1);
            T[i][j].ex=(i?n:mid);
            T[i][j].by=(j?mid+1:1);
            T[i][j].ey=(j?n:mid);
            T[i][j].siz=T[i][j].ey-T[i][j].by+1;
            T[i][j].pre(1,T[i][j].siz,1);
        }
    int m=read();
    for(int i=1;i<=n;++i)
        doModify(n,i,i,read());
    for(int i=0;i<m;++i){
        int op=read();
        int l=read();
        int r=read();
        if(op==1){
            if(l>r)std::swap(l,r);
            int d=read();
            doModify(n,l,r,d);
        }
        else printf("%d\n",doQuery(n,l,r));	
    }
    return 0;
}

