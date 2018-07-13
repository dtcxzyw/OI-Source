#include <cstdio>
#include <algorithm>
int gcd(int a,int b,int& cnt){
	while(b){
		cnt+=a/b;
		a%=b;
		std::swap(a,b);
	}
	return a;
}
const int inf=1<<30;
struct Info{
	int A[3];
	void input(){
		for(int i=0;i<3;++i)scanf("%d",&A[i]);
		std::sort(A,A+3);
	}
	bool operator==(const Info& rhs) const{
		return A[0]==rhs.A[0] && A[1]==rhs.A[1] && A[2]==rhs.A[2];
	}
};
Info jump(Info u,int maxs,int& cnt){
	int d1=u.A[1]-u.A[0],d2=u.A[2]-u.A[1];
	if(d1==d2)return u;
	if(d1<d2){
		int sub=std::min(maxs,(d2-1)/d1);
		maxs-=sub;
		cnt+=sub;
		int off=sub*d1;
		u.A[0]+=off,u.A[1]+=off;
	} 
	else{
		int sub=std::min(maxs,(d1-1)/d2);
		maxs-=sub;
		cnt+=sub;
		int off=sub*d2;
		u.A[1]-=off,u.A[2]-=off;
	}
	if(maxs)return jump(u,maxs,cnt);
	return u;
}
int main(){
	Info A,B;
	A.input();
	B.input();
	int da=0,db=0;
	if(jump(A,inf,da)==jump(B,inf,db)){
		puts("YES");
		if(da<db){
			std::swap(A,B);
			std::swap(da,db);
		}
		int delta=da-db,l=0,r=db,ans=r,x;
		A=jump(A,delta,x);
		while(l<=r){
			int m=(l+r)>>1;
			if(jump(A,m,x)==jump(B,m,x))ans=m,r=m-1;
			else l=m+1;
		}
		printf("%d\n",delta+ans*2);
	}
	else puts("NO");
	return 0;
}

