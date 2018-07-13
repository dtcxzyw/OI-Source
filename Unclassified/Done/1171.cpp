#include <cstdio>
#include <algorithm>
int n,ans=20000,b[20];
std::pair<int,int> w[20][20];
int sum=0,mine[20];
bool flag[20]={};
void DFS(int u,int v,int cnt){
    if(v+sum<ans){
	    if(cnt>1){
	        flag[u]=true;
	        sum-=mine[u];
	        for(int i=1;i<n;++i)
				if(!flag[w[u][i].second])
					DFS(w[u][i].second,v+w[u][i].first,cnt-1);
			sum+=mine[u];
	    	flag[u]=false;
		}
	    else if(ans>v+b[u])
	    	ans=v+b[u];
	}
}
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
int main(){
	n=read();
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            w[i][j].first=read();
            w[i][j].second=j;
		}
		b[i]=w[i][0].first;
		std::sort(w[i],w[i]+n);
		mine[i]=w[i][1].first;
		sum+=mine[i];
    }
    DFS(0,0,n);
    printf("%d\n",ans);
    return 0;
}

