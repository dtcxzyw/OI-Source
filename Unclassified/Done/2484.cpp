#include <cstdio>
#include <cstring>
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
int A[101][101],B[101][101];
int main(){
	int n=read();
	int m=read();
	int sum=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			A[i][j]=read();
			sum+=A[i][j];
		}
	int ans=sum;
	for(int r=1;r<=n;++r)
		for(int c=1;c<=m;++c){
			int s=r*c;
			if(sum%s!=0 || sum/s>=ans)continue;
			memcpy(B,A,sizeof(B));
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					if(B[i][j]){
						int sub=B[i][j];
						if(i+r-1>n || j+c-1>m)goto out;
						for(int x=i;x<i+r;++x)
							for(int y=j;y<j+c;++y)
								if((B[x][y]-=sub)<0)goto out;
					}
			ans=sum/s;
			out:{}
		}
	printf("%d\n",ans);
	return 0;
}

