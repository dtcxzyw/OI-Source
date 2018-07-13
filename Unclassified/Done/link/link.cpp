#include <iostream>
#include <memory.h>
using namespace std;
bool mat[1000][1000],tmp[1000][1000];
int n,m,c,sum,obj;
void dfs(int x,int y)
{
	if(sum==obj)return;
	++sum;
	tmp[x][y]=false;
	if(x>1 && tmp[x-1][y])dfs(x-1,y);
	if(y>1 && tmp[x][y-1])dfs(x,y-1);
	if(x<n && tmp[x+1][y])dfs(x+1,y);
	if(y<m && tmp[x][y+1])dfs(x,y+1);
}
inline bool check(int x,int y)
{
	int sum=0;
	sum+=(x<=1 || !mat[x-1][y]);
	sum+=(y<=1 || !mat[x][y-1]);
	sum+=(x>=n || !mat[x+1][y]);
	sum+=(y>=m || !mat[x][y+1]);
	return sum>=3;
}
int foo()
{
	cin>>n>>m>>c;
	memset(mat,1,sizeof(mat));
	for(int i=0;i<c;++i)
	{
		int x,y;
		cin>>x>>y;
		mat[x][y]=false;
	}
	memcpy(tmp,mat,sizeof(mat));
	if((n==1 && m==1) || n*m-c<2)return -1;
	else
	{
		sum=0,obj=n*m-c;;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			if(mat[i][j])
			{
				dfs(i,j);
				goto point;
			}
		point:
		if(sum!=obj)return 0;
		if(obj==2)return -1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(check(i,j))
					return 1;
		return 2;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	for(int i=0;i<t;++i)
		cout<<foo()<<endl;
	return 0;	
}

