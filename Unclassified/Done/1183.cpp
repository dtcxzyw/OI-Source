#include <cstdio>
int P[100][2];
int calc(int a,int b){
	int dax=P[0][0]-P[a][0],
		day=P[0][1]-P[a][1],
		dbx=P[0][0]-P[b][0],
		dby=P[0][1]-P[b][1];
	return dax*dby-day*dbx;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&P[i][0],&P[i][1]);
	int S=0;
	for(int i=2;i<n;++i)
		S+=calc(i-1,i);
	printf("%d\n",S>>1);
	return 0;
}

