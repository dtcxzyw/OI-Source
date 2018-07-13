#include <cstdio>
#include <cmath>
int A[40];
bool flag[810][810]={};
int S(int a,int b,int c){
	double p=(a+b+c)/2.0;
	double s2=p*(p-a)*(p-b)*(p-c);
	return s2>0.0?static_cast<int>(sqrt(s2)*100.0):-1;
}
int main(){
	int n,len=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&A[i]);
		len+=A[i];
	}
	int limit=len>>1,ans=-1;
	flag[0][0]=true;
	for(int i=0;i<n;++i)
		for(int j=limit;j>=0;--j)
			for(int k=len-j-1;k>=0;--k){
				flag[j][k]|=(j>=A[i] && flag[j-A[i]][k]);
				flag[j][k]|=(k>=A[i] && flag[j][k-A[i]]);
				if(flag[j][k]){
					int s=S(j,k,len-j-k);
					if(ans<s)ans=s;
				}	
			}
	printf("%d\n",ans);
	return 0;
}

