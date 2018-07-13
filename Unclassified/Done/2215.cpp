#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	if(x<0)putchar('-'),x=-x;
	printImpl(x);
	putchar(' ');
}
int maxv(int a,int b){
    return a>b?a:b;
}
const int size=10010;
int A[size],len[size],B[size]={};
int find(int r,int x){
    int l=1,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(B[mid]>x)res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i)A[i]=read();
	int ml=0;
	for(int i=n;i>=1;--i){
		int l=find(ml,A[i])+1;
		len[i]=l;
		B[l]=maxv(B[l],A[i]);
		ml=maxv(ml,l);
	}
	int m=read();
	for(int i=0;i<m;++i){
		int l=read();
		if(l>ml)puts("Impossible");
		else{
			if(l>0){
				for(int j=1,last=-1<<30;j<=n;++j)
					if(len[j]>=l && A[j]>last){
						last=A[j];
						print(last);
						if((--l)==0)break;
					}
			}
			putchar('\n');
		}
	}
	return 0;
}

