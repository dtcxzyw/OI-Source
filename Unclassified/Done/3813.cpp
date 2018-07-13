#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long Int64;
const Int64 mod=1000000007LL;
Int64 powm(Int64 a,Int64 k){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
Int64 find(Int64* A,Int64 siz,Int64 x){
	return std::lower_bound(A,A+siz,x)-A;
}
Int64 clamp(Int64 a){
	return (a%mod+mod)%mod;
}
const Int64 size=100;
struct Rect{
	Int64 bx,by,ex,ey,v;
} R[size];
Int64 X[size],Y[size];
Int64 mat[size][size],mask[size][size];//[X[i],X[i+1])
Int64 val[size*size],siz[size*size],op[size*size],dp[2][1<<10];
void foo(){
	Int64 h,w,m,n;
	scanf("%lld%lld%lld%lld",&h,&w,&m,&n);
	X[0]=Y[0]=1;
	Int64 cnt=0;
	for(Int64 i=1;i<=n;++i){
		scanf("%lld%lld%lld%lld%lld",&R[i].bx,&R[i].by,&R[i].ex,&R[i].ey,&R[i].v);
		++cnt;
		X[cnt]=R[i].bx,Y[cnt]=R[i].by;
		++R[i].ex,++R[i].ey;
		++cnt;
		X[cnt]=R[i].ex,Y[cnt]=R[i].ey;
	}
	++cnt;
	X[cnt]=h+1,Y[cnt]=w+1;
	std::sort(X,X+cnt+1);
	Int64 sx=std::unique(X,X+cnt+1)-X;
	std::sort(Y,Y+cnt+1);
	Int64 sy=std::unique(Y,Y+cnt+1)-Y;
	for(Int64 i=0;i<sx;++i)
		for(Int64 j=0;j<sy;++j)
			mat[i][j]=m,mask[i][j]=0;
	for(Int64 i=1;i<=n;++i){
		Int64 bx=find(X,sx,R[i].bx),ex=find(X,sx,R[i].ex);
		Int64 by=find(Y,sy,R[i].by),ey=find(Y,sy,R[i].ey);
		for(Int64 x=bx;x<ex;++x)
			for(Int64 y=by;y<ey;++y)
				if(mat[x][y]>R[i].v)
					mat[x][y]=R[i].v;
	}
	for(Int64 i=1;i<=n;++i){
		Int64 bx=find(X,sx,R[i].bx),ex=find(X,sx,R[i].ex);
		Int64 by=find(Y,sy,R[i].by),ey=find(Y,sy,R[i].ey);
		for(Int64 x=bx;x<ex;++x)
			for(Int64 y=by;y<ey;++y)
				if(mat[x][y]==R[i].v)
					mask[x][y]|=1<<(i-1);
	}
	Int64 bcnt=0;
	for(Int64 i=0;i<sx-1;++i)
		for(Int64 j=0;j<sy-1;++j){
			++bcnt;
			siz[bcnt]=(X[i+1]-X[i])*(Y[j+1]-Y[j]);
			val[bcnt]=mat[i][j];
			op[bcnt]=mask[i][j];			
		}
	
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	Int64 l,c,end=(1<<n)-1;
	for(Int64 i=0;i<bcnt;++i){
		l=i&1,c=1-l;
		memset(dp[c],0,sizeof(dp[c]));
		for(Int64 s=0;s<=end;++s)
			if(dp[l][s]){
				Int64 p1=powm(val[i+1],siz[i+1]);
				Int64 p2=powm(val[i+1]-1,siz[i+1]);
				dp[c][s|op[i+1]]=clamp(dp[c][s|op[i+1]]+dp[l][s]*clamp(p1-p2));
				dp[c][s]=clamp(dp[c][s]+dp[l][s]*p2);
			}
	}
	printf("%lld\n",dp[c][end]);
}
int main(){
	Int64 t;
	scanf("%lld",&t);
	for(Int64 i=0;i<t;++i)foo();
	return 0;
}

