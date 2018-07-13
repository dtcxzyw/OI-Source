#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
const int size=100010;
int input[size][2],map[size<<1],siz;
long long A[size<<2]={};
struct Range{
	int x,s;
} B[size<<2];
void add(int i,int d){
	while(i<=(siz<<1)){
		A[i]+=d;
		i+=i&-i;
	}
}
long long query(int i){
	long long ans=0;
	while(i){
		ans+=A[i];
		i-=i&-i;
	}
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&input[i][0],&input[i][1]);
	memcpy(map,input,sizeof(int)*n<<1);
	std::sort(map,map+(n<<1));
	siz=std::unique(map,map+(n<<1))-map;
	
	for(int i=0;i<n;++i)
		for(int j=0;j<2;++j)
			input[i][j]=std::lower_bound(map,map+siz,input[i][j])-map;
	
	for(int i=0;i<siz;++i){
		B[i<<1]=Range{i<<1,1};
		if(i<siz-1)
			B[i<<1|1]=Range{i<<1|1,map[i+1]-map[i]-1};
	}

	for(int i=0;i<n;++i)
		std::swap(B[input[i][0]<<1],B[input[i][1]<<1]);
	
	long long ans=0;
	for(int i=(siz-1)<<1;i>=0;--i){
		ans+=query(B[i].x)*B[i].s;
		add(B[i].x+1,B[i].s);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}

