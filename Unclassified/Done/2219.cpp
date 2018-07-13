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
const int size=1010;
int S[size][size],S1[size][size],S2[size][size],M1[size][size],M2[size][size];
int calc(int bx,int by,int ex,int ey){
	return S[ex][ey]-S[bx][ey]-S[ex][by]+S[bx][by];
}
struct Q{
	int b,e,qi[size],qv[size];
	void clear(){
		b=e=0;
	}
	void pop(int x){
		while(b!=e && qi[b]<x)++b;
	}
	void push(int x,int y){
		while(b!=e && qv[e-1]>y)--e;
		qi[e]=x,qv[e]=y;
		++e;
	}
	int front() const{
		return qv[b];
	}
} q;
int main(){
	int n=read();
	int m=read();
	int a=read();
	int b=read();
	int c=read();
	int d=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			S[i][j]=S[i-1][j]+S[i][j-1]+read()-S[i-1][j-1];
	for(int i=a;i<=n;++i)
		for(int j=b;j<=m;++j)
			S1[i][j]=calc(i-a,j-b,i,j);
	for(int i=c;i<=n;++i)
		for(int j=d;j<=m;++j)
			S2[i][j]=calc(i-c,j-d,i,j);
	int ox=c-a+2,oy=d-b+2;
	for(int i=1;i<=n;++i){
		q.clear();
		for(int j=1;j<=m;++j){
			q.pop(j+oy);
			q.push(j,S2[i][j]);
			M1[i][j]=q.front();
		}
	}
	
	for(int i=1;i<=m;++i){
		q.clear();
		for(int j=1;j<=n;++j){
			q.pop(j+ox);
			q.push(j,M1[j][i]);
			M2[j][i]=q.front();
		}
	}
	
	int res=0;
	for(int i=a;i<=n;++i)
		for(int j=b;j<=m;++j){
			int val=S1[i][j]-M2[i-1][j-1];
			if(res<val)res=val;
		}
	printf("%d\n",res);
	return 0;
}

