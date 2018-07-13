#include <cstdio>
const int size=100100;
struct Info{
	double a,b;
	double calc(double A,double B) const{
		return A*a+B*b;
	}
} L[size];
int nxt[size]={},pre[size]={},head=0,tail=0;
void erase(int i){
	int p=pre[i],n=nxt[i];
	pre[n]=p,nxt[p]=n;
	if(n==0)tail=p;
	if(p==0)head=n;
}
int main(){
	int n,s;
	scanf("%d%d",&n,&s);
	double ans=s;
	for(int i=1;i<=n;++i){
		double A,B,R;
		scanf("%lf%lf%lf",&A,&B,&R);
		R*=A/B;
		for(int j=head;j;j=nxt[j]){
			double val=L[j].calc(A,B);
			if(ans<val)ans=val;
		}
		double wa=R/(R+1.0),wb=1.0/(R+1.0);
		double na=ans*wa/A,nb=ans*wb/B;
		for(int j=head;j;j=nxt[j])
			if(L[j].a<=na && L[j].b<=nb)
				erase(j);
		++tail;
		if(head==0)head=tail;
		L[tail].a=na,L[tail].b=nb;
		nxt[tail-1]=tail;
		pre[tail]=tail-1;
	}
	printf("%.3lf\n",ans);
	return 0;
}

