#include <cstdio>
const int size=10,scnt=1<<size,esiz=size*size/2+10;
int edge[size];
long long C[esiz][esiz],f[scnt][esiz]={},g[scnt][esiz]={},cnt[scnt]={},bcnt[scnt];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	C[0][0]=1;
	for(int i=1;i<=m;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=0;i<m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		--u,--v;
		edge[u]|=1<<v;
		edge[v]|=1<<u;
	}
	int end=1<<n;
	bcnt[0]=0;
	for(int i=1;i<end;++i){
		bcnt[i]=bcnt[i>>1]+(i&1);
		if(bcnt[i]==1)g[i][0]=1;
		else{
			for(int j=0;j<n;++j)
				if(i&(1<<j))
					cnt[i]+=bcnt[edge[j]&i];
			cnt[i]>>=1;
			int p=i&-i;
			for(int s=i&(i-1);s;s=(s-1)&i)if(s&p)
				for(int j=0;j<=cnt[s];++j){
					int sub=i^s;
					for(int k=0;k<=cnt[sub];++k)
						f[i][j+k]+=g[s][j]*C[cnt[sub]][k];
				}
			for(int j=0;j<=cnt[i];++j)
				g[i][j]=C[cnt[i]][j]-f[i][j];
		}
	}
	double ans=0.0;
	int all=end-1;
	for(int i=0;i<=cnt[all];++i)
		ans+=static_cast<double>(f[all][i])/C[cnt[all]][i];
	printf("%.6lf\n",ans/(m+1));
	return 0;
}

