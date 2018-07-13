#include <cstdio>
#include <algorithm>
#include <functional>
int len[70],sum=0,n,ol;
bool flag[70]={},p=false;
void dfs(int cl,int cnt,int b){
	if(p)return;
	if(ol*cnt==sum){
		p=true;
		return;
	}
	if(cl==ol)dfs(0,cnt+1,1);
	else{
		for(;b<n;++b)
			if(!flag[b] && cl+len[b]<=ol){
				flag[b]=true;
				dfs(cl+len[b],cnt,b+1);
				flag[b]=false;
				if(cl==0 || cl+len[b]==ol)break;
				while(len[b]==len[b+1])++b;
			}
	}
}
int main(){
	int cnt=0;
	scanf("%d",&n);
	int x;
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		if(x<=50)len[cnt++]=x;
	}
	n=cnt;
	std::sort(len,len+n,std::greater<int>());
	int maxv=0;
	for(int i=0;i<n;++i){
		sum+=len[i];
		if(len[i]>maxv)maxv=len[i];
	}
	
	for(ol=maxv;ol<=sum;++ol)
		if(sum%ol==0){
			dfs(0,0,0);
			if(p){
				printf("%d\n",ol);
				break;
			}
		}
	return 0;
}

