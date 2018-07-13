#include <cstdio>
int p[11],k;
bool add(int i){
	if(p[i]+1==p[i+1]){
		if(add(i+1)){
			for(int j=0;j<=i;++j)
				p[j]=j;
			return false;
		}
	}
	else {
		++p[i];
		return true;
	}
}
int main(){
	int n;
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;++i)
		p[i]=i;
	for(int i=1;i<n;++i)add(0);
	for(int i=k-1;i>=0;--i){
		putchar('1');
		for(int j=p[i]-(i?p[i-1]+1:0);j>0;--j)putchar('0');
	}
	puts("");
	return 0;
}

