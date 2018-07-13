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
long long A[size],L[size][size],R[size][size];
bool foo(){
	int n=read();
	for(int i=1;i<=n;++i)
		L[i][i]=R[i][i]=A[i]=read();
	for(int i=2;i<=n;++i)
		for(int l=0;l+i-1<=n;++l){
			int r=l+i-1;
			{
				int lv=L[l][r-1],rv=R[l][r-1],v=A[r];
				if(v==rv)L[l][r]=0;
				else if((v<lv && v<rv) || (v>lv && v>rv))L[l][r]=v;
				else if(lv<=v && v<=rv)L[l][r]=v+1;
				else L[l][r]=v-1;
			}
			{
				int lv=L[l+1][r],rv=R[l+1][r],v=A[l];
				if(v==rv)R[l][r]=0;
				else if((v<lv && v<rv) || (v>lv && v>rv))R[l][r]=v;
				else if(lv<=v && v<=rv)R[l][r]=v+1;
				else R[l][r]=v-1;
			}
		}
	return L[2][n]!=A[1];
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)puts(foo()?"1":"0");
	return 0;
}

