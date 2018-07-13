#include <cstdio>
#include <cstring>
int N[11],A[11][10][10],B[11][2],LUT[10][10];
int query(int n){
	if(n==0)return 0;
	int siz=0;
	while(n){
		N[++siz]=n%10;
		n/=10;
	}
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
	for(int i=0;i<10;++i)A[1][i][i]=1;
	for(int i=2;i<=siz;++i){
		for(int j=0;j<10;++j)
			for(int k=0;k<10;++k)
				for(int s=0;s<10;++s)
					if(LUT[k][s])
						A[i][j][k]+=A[i-1][j][s];
	}
	int ans=0;
	for(int i=1;i<siz;++i)
		for(int j=1;j<10;++j)
			for(int k=0;k<10;++k)
				ans+=A[i][j][k];
	for(int i=siz;i;--i){
		for(int j=siz-1;j>i;--j)
			if(!LUT[N[j]][N[j+1]])
				return ans;
		for(int j=(i==siz);j<N[i];++j)if(i==siz || LUT[N[i+1]][j])
			for(int k=0;k<10;++k)
				ans+=A[i][j][k];
	}
	return ans;
}
int main(){
	for(int i=0;i<10;++i)
		for(int j=0;j<10;++j){
			int d=i-j;
			LUT[i][j]=(d<=-2 || d>=2);
		}
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%d\n",query(b+1)-query(a));
	return 0;
}

