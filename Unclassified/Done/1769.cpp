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
double A[1024][1024],B[11][1024]={};
int main(){
	int n=read();
	int m=1<<n;
	for(int i=0;i<m;++i)
		for(int j=0;j<m;++j)
			A[i][j]=read()/100.0;
	for(int i=0;i<m;++i)
		B[0][i]=1.0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<m;++j){
			int l=j>>i<<i,r=l+(1<<i);
			double c=0.0;
			for(int k=l;k<r;++k)
				c+=A[j][k]*B[i-1][k];
			l=j>>(i-1)<<(i-1),r=l+(1<<(i-1));
			for(int k=l;k<r;++k)
				c-=A[j][k]*B[i-1][k];
			B[i][j]=c*B[i-1][j];
		}
	}
	
	double maxv=0.0;
	int maxwell;
	for(int i=0;i<m;++i)
		if(B[n][i]>maxv)
			maxwell=i,maxv=B[n][i];
	printf("%d\n",maxwell+1);
	return 0;
}

