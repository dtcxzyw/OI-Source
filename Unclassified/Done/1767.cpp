#include <cstdio>
#include <cctype>
char mat[102][202]={};
bool flag[102][202]={};
void color(int x,int y){
	if(flag[x][y])return;
	flag[x][y]=true;
	if(isalpha(mat[x-1][y]))color(x-1,y);
	if(isalpha(mat[x][y-1]))color(x,y-1);
	if(isalpha(mat[x+1][y]))color(x+1,y);
	if(isalpha(mat[x][y+1]))color(x,y+1);
}
bool in(char x){
	return isalpha(x)||x==' '||x=='*';
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		do gets(mat[i]+1);
		while(!in(mat[i][1]));
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;mat[i][j];++j)
			if(isalpha(mat[i][j]) && !flag[i][j]){
				++ans;
				color(i,j);
			}
	printf("%d\n",ans);
	return 0;
}

