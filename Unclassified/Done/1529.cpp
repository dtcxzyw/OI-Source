#include <cstdio>
#include <cstring>
int dis[52][52];
bool flag[26];
int map(char c){
	if('a'<=c && c<='z')return c-'a';
	else{
		if(c!='Z')flag[c-'A']=true;
		return c-'A'+26;
	}
}
void CAS(int& a,int b){
	if(a>b)a=b;
}
int main(){
	int n;
	scanf("%d",&n);
	char u[2],v[2];
	int w;
	memset(dis,0x3f,sizeof(dis));
	for(int i=0;i<52;++i)
		dis[i][i]=0;
	for(int i=0;i<n;++i){
		scanf("%s%s%d",u,v,&w);
		CAS(dis[map(*u)][map(*v)],w);
		CAS(dis[map(*v)][map(*u)],w);
	}
	for(int k=0;k<52;++k)
		for(int i=0;i<52;++i)
			for(int j=0;j<52;++j)
				CAS(dis[i][j],dis[i][k]+dis[k][j]);
	char maxc;
	int minv=0x3f3f3f3f;
	for(char i='A';i<'Z';++i)
		if(flag[i-'A'] && dis[map(i)][51]<minv)
			maxc=i,minv=dis[map(i)][51];
	printf("%c %d\n",maxc,dis[map(maxc)][51]);
	return 0;
}

