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
int getOp(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c;
}
const int offset=201000,end=offset*2,size=end+200;
int sum[size<<2]={},cnt=0;
bool lazy[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int k;
void push(int id){
	if(lazy[id]){
		sum[id<<1]=sum[id<<1|1]=0;
		lazy[id<<1]=lazy[id<<1|1]=true;
		lazy[id]=false;
	}
}
void insert(int l,int r,int id){
	++sum[id];
	if(l!=r){
		push(id);
		int m=(l+r)>>1;
		if(k<=m)insert(ls);
		else insert(rs);
	}
}
void clear(int l,int r,int id){
	if(sum[id]){
		if(r<=k){
			cnt+=sum[id];
			sum[id]=0;
			lazy[id]=true;
		}
		else{
			push(id);
			int m=(l+r)>>1;
			clear(ls);
			if(m<k)clear(rs);
			sum[id]=sum[id<<1]+sum[id<<1|1];
		}
	}
}
int query(int l,int r,int id){
	if(l==r)return l;
	else{
		push(id);
		int m=(l+r)>>1,rsiz=sum[id<<1|1];
		if(k<=rsiz)return query(rs);
		k-=rsiz;
		return query(ls);
	}
}
int main(){
	int n=read();
	int minv=read();
	int base=0;
	for(int i=0;i<n;++i){
		int op=getOp();
		k=read();
		switch(op){
			case 'I':{
				if(k>=minv){
					k=k-base+offset;
					insert(1,end,1);
				}
			}break;
			case 'A':base+=k;break;
			case 'S':{
				base-=k;
				//v=x-offset+base>=minv
				//x>=minv-base+offset
				k=minv-base+offset-1;
				if(k>=1)clear(1,end,1);
			}break;
			case 'F':{
				if(sum[1]>=k)printf("%d\n",query(1,end,1)-offset+base);
				else puts("-1");
			}break;
		}
	}
	printf("%d\n",cnt);
	return 0;
}

