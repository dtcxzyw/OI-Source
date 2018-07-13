#include <cstdio>
int getBit(){
	int c;
	do c=getchar();
	while(c!='0'&&c!='1');
	return c-'0';
}
int minv(int a,int b){
	return a<b?a:b;
}
int maxv(int a,int b){
	return a>b?a:b;
}
const int size=2010;
int A[size][size],len[size][size],sta[size][2],top=0,L1=0,S2=0;
void push(int x,int r){
	int mx=x;
	while(top && sta[top][0]>r){
		L1=maxv(L1,minv(x-sta[top][1],sta[top][0]));
		S2=maxv(S2,(x-sta[top][1])*sta[top][0]);
		mx=sta[top][1];
		--top;
	}
	++top;
	sta[top][0]=r;
	sta[top][1]=mx;
}
void slove(int n,int m,int x){
	for(int i=1;i<=n;++i)
		for(int j=m;j>=1;--j)
			len[i][j]=(A[i][j]==x?len[i][j+1]+1:0);
	for(int j=1;j<=m;++j){
		top=0;
		for(int i=1;i<=n;++i)
			push(i,len[i][j]);
		push(n+1,0);
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			A[i][j]=getBit()^((i+j)&1);
	slove(n,m,0);
	slove(n,m,1);
	printf("%d\n%d\n",L1*L1,S2);
	return 0;
}

