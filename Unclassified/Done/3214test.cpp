#include <cstdio>
#include <vector>
std::vector<std::vector<int> > set;
int n,m,res=0,cnt[100]={};
bool choose[100]={};
void dfs(int a,int b){
	if(b==m){
		for(int i=1;i<=n;++i)
			if(cnt[i]&1)return;
		for(int i=1;i<set.size();++i)
			if(choose[i]){
				putchar('{');
				for(int j=0;j<set[i].size();++j)
					printf("%d ",set[i][j]);
				putchar('}');
			}
		puts("");
		++res;
		return;
	}
	if(set.size()-a<m-b)return;
	dfs(a+1,b);
	choose[a]=true;
	for(int i=0;i<set[a].size();++i)
		++cnt[set[a][i]];
	dfs(a+1,b+1);
	choose[a]=false;
	for(int i=0;i<set[a].size();++i)
		--cnt[set[a][i]];
}
int main(){
	scanf("%d%d",&n,&m);
	set.push_back(std::vector<int>());
	for(int i=1;i<=n;++i){
		int siz=set.size();
		for(int j=0;j<siz;++j){
			std::vector<int> tmp=set[j];
			tmp.push_back(i);
			set.push_back(tmp);
		}
	}
	printf("%d\n",int(set.size()-1));
	dfs(1,0);
	printf("%d\n",res);
	return 0;
}

