#include <cstdio>
const int size=100000<<2;
double ssum[size]={},sum[size]={},lazy[size]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1

void update(int id){
    ssum[id]=ssum[id<<1]+ssum[id<<1|1];
    sum[id]=sum[id<<1]+sum[id<<1|1];
}

void color(int l,int r,int id,double add){
	double x=add*(r-l+1);
	ssum[id]+=add*(2.0*sum[id]+x);
	sum[id]+=x;
	lazy[id]+=add;
}

void push(int l,int r,int id){
	if(lazy[id]!=0.0){
		int m=(l+r)>>1;
		color(ls,lazy[id]);
		color(rs,lazy[id]);
		lazy[id]=0.0;
	}
}

void modify(int l,int r,int id,int nl,int nr,double add){
    if(nl<=l && r<=nr)color(l,r,id,add);
    else{
    	push(l,r,id);
        int m=(l+r)>>1;
        if(nl<=m)modify(ls,nl,nr,add);
        if(m<nr)modify(rs,nl,nr,add);
        update(id);
    }
}

double querySum(int l,int r,int id,int nl,int nr){
    if(nl<=l && r<=nr)return sum[id];
    else{
    	push(l,r,id);
        int m=(l+r)>>1;
        double ans=0.0;
        if(nl<=m)ans+=querySum(ls,nl,nr);
        if(m<nr)ans+=querySum(rs,nl,nr);
        return ans;
    }
}

double querySS(int l,int r,int id,int nl,int nr){
    if(nl<=l && r<=nr)return ssum[id];
    else{
    	push(l,r,id);
        int m=(l+r)>>1;
        double ans=0.0;
        if(nl<=m)ans+=querySS(ls,nl,nr);
        if(m<nr)ans+=querySS(rs,nl,nr);
        return ans;
    }
}

void build(int l,int r,int id){
    if(l==r){
        scanf("%lf",&sum[id]);
        ssum[id]=sum[id]*sum[id];
    }
    else{
        int m=(l+r)>>1;
        build(ls);
        build(rs);    
        update(id);
    }
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    build(1,n,1);
    int c,l,r;
    double k;
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&c,&l,&r);
        int size=r-l+1;
        switch(c){
            case 1:{
                scanf("%lf",&k);
                modify(1,n,1,l,r,k);
            }break;
            case 2:printf("%.4lf\n",querySum(1,n,1,l,r)/size);break;
            case 3:{
                double mean=querySum(1,n,1,l,r)/size;
                double ss=querySS(1,n,1,l,r)/size;
                printf("%.4lf\n",ss-mean*mean);
            }break;
        }
    }
    return 0;
}

