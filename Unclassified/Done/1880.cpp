#include <cstdio>
const int size=210;
int minv[size][size],maxv[size][size],A[size],sum[size];
void smin(int& a,int b){
	if(a>b)a=b;
}
void smax(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n;
	scanf("%d",&n);
	sum[0]=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);
		A[i+n]=A[i];
	}
	int num=n<<1;
	for(int i=1;i<num;++i)
		sum[i]=sum[i-1]+A[i];
		
	for(int k=2;k<=n;++k)
		for(int j=k;j<num;++j){
			int i=j-k+1,s=sum[j]-sum[i-1];
			minv[i][j]=1<<30,maxv[i][j]=0;
			for(int m=i;m<j;++m){
				smin(minv[i][j],minv[i][m]+minv[m+1][j]+s);
				smax(maxv[i][j],maxv[i][m]+maxv[m+1][j]+s);
			}
		}
		
	int amin=1<<30,amax=0;
	for(int i=1;i<=n;++i){
		smin(amin,minv[i][i+n-1]);
		smax(amax,maxv[i][i+n-1]);
	}
	printf("%d\n%d\n",amin,amax);
	return 0;	
}

