#include <cstdio>
const int size=60;
char buf[size];
int maxd[size][size],mind[size][size];
void CASmax(int& a,int b){
	if(a<b)a=b;
}
void CASmin(int& a,int b){
	if(a>b)a=b;
}
bool equal(int a,int b,int c,int d){
	return a==b && b==c && c==d;
}
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i){
		scanf("%s",buf+1);
		buf[i]='=';
		for(int j=1;j<=n;++j)
			if(buf[j]=='+')maxd[i][j]=2,mind[i][j]=1;
			else if(buf[j]=='-')maxd[i][j]=-1,mind[i][j]=-2;
			else if(buf[j]=='=')maxd[i][j]=mind[i][j]=0;
			else maxd[i][j]=2,mind[i][j]=-2;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)if(i!=k)
			for(int j=1;j<=n;++j)if(i!=j && j!=k){
				CASmin(maxd[i][j],maxd[i][k]+maxd[k][j]);
				CASmax(mind[i][j],mind[i][k]+mind[k][j]);
			}
	int c1=0,c2=0,c3=0;
	for(int i=1;i<=n;++i)if(i!=a && i!=b)
		for(int j=i+1;j<=n;++j)if(j!=a && j!=b){
			//a-i>j-b b-i>j-a
			if(mind[a][i]>maxd[j][b] || mind[b][i]>maxd[j][a])++c1;
			//a-i<j-b b-i<j-a
			if(maxd[a][i]<mind[j][b] || maxd[b][i]<mind[j][a])++c3;
			//a-i==j-b b-i==j-a
			if(equal(maxd[a][i],mind[a][i],maxd[j][b],mind[j][b])||
				equal(maxd[b][i],mind[b][i],maxd[j][a],mind[j][a]))++c2;
		}
	printf("%d %d %d\n",c1,c2,c3);
	return 0;
}

