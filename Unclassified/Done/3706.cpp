#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
const int size=305;
char P[size*2];
double seq[size];
int fail[size*2];
double calc(const char* A,const char* B,int siz){
	memcpy(P+1,A,siz);
	memcpy(P+siz+1,B,siz);
	fail[1]=0;
	int n=siz<<1;
	for(int i=2;i<=n;++i){
		int pos=fail[i-1];
		while(pos && P[i]!=P[pos+1])pos=fail[pos];
		fail[i]=(P[i]==P[pos+1]?pos+1:0);
	}
	double res=0.0;
	int x=fail[n];
	while(x>siz)x=fail[x];
	while(x){
		res+=seq[siz-x];
		x=fail[x];
	}
	return res;
}
double A[size][size],B[size]={},ans[size];
void solve(int n){
    for(int i=1;i<=n;++i){
        int x=i;
        for(int j=i+1;j<=n;++j)
            if(fabs(A[x][i])<fabs(A[j][i]))
                x=j;
        if(x!=i){
            for(int j=i;j<=n;++j)
                std::swap(A[x][j],A[i][j]);
            std::swap(B[x],B[i]);
        }
        for(int j=i+1;j<=n;++j){
            double mul=A[j][i]/A[i][i];
            for(int k=i;k<=n;++k)
                A[j][k]-=A[i][k]*mul;
            B[j]-=B[i]*mul;
        }
    }
    for(int i=n;i>=1;--i){
        double sum=B[i];
        for(int j=i+1;j<=n;++j)
            sum-=ans[j]*A[i][j];
        ans[i]=sum/A[i][i];
    }
}
char buf[size][size];
void buildMat(int n,int m){
	seq[0]=1.0;
	for(int i=1;i<=m;++i)seq[i]=seq[i-1]*0.5;
	for(int i=1;i<=n;++i)A[n+1][i]=1.0;
	B[n+1]=1.0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			A[i][j]=calc(buf[i],buf[j],m);
		A[i][n+1]=-seq[m];
	}
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%s",buf[i]);
    buildMat(n,m);
    solve(n+1);
    for(int i=1;i<=n;++i)
        printf("%.10lf\n",ans[i]);
    return 0;
}

