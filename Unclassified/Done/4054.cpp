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
const int size=301;
int n,m,A[size][size],S[101][size][size]={};
void modify(int c,int x,int y,int op){
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=m;j+=j&-j)
			S[c][i][j]+=op;
}
int query(int c,int x,int y){
	int res=0;
	for(int i=x;i;i-=i&-i)
		for(int j=y;j;j-=j&-j)
			res+=S[c][i][j];
	return res;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			A[i][j]=read();
			modify(A[i][j],i,j,1);
		}
	}
	int q=read();
	for(int i=0;i<q;++i)
		if(read()==1){
			int x=read();
			int y=read();
			int c=read();
			modify(A[x][y],x,y,-1);
			A[x][y]=c;
			modify(c,x,y,1);
		}
		else{
			int bx=read()-1;
			int ex=read();
			int by=read()-1;
			int ey=read();
			int c=read();
			printf("%d\n",query(c,ex,ey)-query(c,bx,ey)-query(c,ex,by)+query(c,bx,by));
		}
	return 0;
}

