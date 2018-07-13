#include <cstdio>
#include <algorithm>
const int maxn=500010;
std::pair<int,int> stack[maxn];
int getInt(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while(c>='0' && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}

int main(){
    int n=getInt(),ans=0,size=0;
    for(int i=1;i<=n;++i){
    	int x=getInt();
		while(size && stack[size].first<x){
			ans+=stack[size].second;
			--size;
		}
		if(size && stack[size].first==x)
			ans+=(size>1)+stack[size].second++;
		else{
			if(size)++ans;
			stack[++size]=std::make_pair(x,1);
		}
    }
    
    printf("%d\n",ans);
    return 0;
}

