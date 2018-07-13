#include <cstdio>
#include <algorithm>
#include <map>
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
int getAlpha(){
	int c;
	do c=getchar();
	while(c!='A' && c!='B');
	return c;
}
int iabs(int x){
	return x>0?x:-x;
}
const int size=100005;
int A[size][4],minv=1<<30,maxv=0;
std::map<std::pair<int,int>,long long> cache;
long long calc0(int cnt,int x,int y){
	int l,r;
	if(y==-1)l=r=x;
	else l=std::min(x,y),r=std::max(x,y);
	long long& res=cache[std::make_pair(l,r)];
	if(!res){
		for(int i=0;i<cnt;++i){
			if(A[i][1]<=l)res+=1LL+(l<<1)-A[i][2];
			else if(A[i][0]>=r)res+=1LL+A[i][2]-(r<<1);
			else if(l<=A[i][0] && A[i][1]<=r)res+=1LL+std::min(A[i][2]-(l<<1),(r<<1)-A[i][2]);
			else res+=A[i][3]+1LL;
		}
	}
	return res;
}
long long calc1(int cnt,int x){
	long long l=minv,r=maxv;
	while(r-l>=3){
		int lm=((l<<1)+r)/3;
		int rm=(l+(r<<1))/3;
		if(calc0(cnt,lm,x)<calc0(cnt,rm,x))r=rm;
		else l=lm;
	}
	long long ans=1LL<<60;
	for(int i=l;i<=r;++i)
		ans=std::min(ans,calc0(cnt,i,x));
	return ans;
}
long long calc2(int cnt){
	long long l=minv,r=maxv;
	while(r-l>=3){
		int lm=((l<<1)+r)/3;
		int rm=(l+(r<<1))/3;
		if(calc1(cnt,lm)<calc1(cnt,rm))r=rm;
		else l=lm;
	}
	long long ans=1LL<<60;
	for(int i=l;i<=r;++i)
		ans=std::min(ans,calc1(cnt,i));
	return ans;
}
int main(){
	int k=read();
	int n=read();
	long long ans=0;
	int cnt=0;
	for(int i=0;i<n;++i){
		int pa=getAlpha();
		int qa=read();
		int pb=getAlpha();
		int qb=read();
		if(pa==pb)ans+=iabs(qa-qb);
		else{
			A[cnt][0]=std::min(qa,qb),A[cnt][1]=std::max(qa,qb);
			A[cnt][2]=qa+qb,A[cnt][3]=A[cnt][1]-A[cnt][0];
			minv=std::min(minv,A[cnt][0]);
			maxv=std::max(maxv,A[cnt][1]);
			++cnt;
		}
	}
	ans+=(k==1?calc1(cnt,-1):calc2(cnt));
	printf("%lld\n",ans);
	return 0;
}

