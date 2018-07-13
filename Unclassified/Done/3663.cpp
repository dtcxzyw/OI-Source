#include <cstdio>
#include <algorithm>
#include <map>
bool flag[101][101][4]={};//up down left right
const int off[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int color[101][101]={},col=0;
void dfs(char x,char y){
	if(!color[x][y]){
		color[x][y]=col;
		for(char i=0;i<4;++i)
			if(!flag[x][y][i])
				dfs(x+off[i][0],y+off[i][1]);
	}
}
int main(){
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=n;++i)
		flag[1][i][2]=flag[i][1][0]=flag[n][i][3]=flag[i][n][1]=true;
	int x1,y1,x2,y2;
	for(int i=0;i<m;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1==x2){
			if(y1>y2)std::swap(y1,y2);
			flag[x1][y1][1]=flag[x1][y2][0]=true;
		}
		else{
			if(x1>x2)std::swap(x1,x2);
			flag[x1][y1][3]=flag[x2][y1][2]=true;
		}
	}
	
	for(char i=1;i<=n;++i)
		for(char j=1;j<=n;++j)
			if(!color[i][j]){
				++col;
				dfs(i,j);
			}
	std::map<int,int> table;
	int x,y;
	for(int i=0;i<k;++i){
		scanf("%d%d",&x,&y);
		++table[color[x][y]];
	}
	int cnt=0;
	long long sum=0,ans=0;
	for(std::map<int,int>::iterator it=table.begin();it!=table.end();++it){
		int num=it->second;
		ans+=sum*num;
		sum+=num;
	}
	printf("%lld\n",ans);
	return 0;
}

