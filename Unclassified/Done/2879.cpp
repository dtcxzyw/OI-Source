#include <cstdio>
#include <algorithm>
using namespace std;
int sum[10002];
pair<int,int> input[10000];
int main(){
	int N,I,H,R;
	scanf("%d%d%d%d",&N,&I,&H,&R);
	int a,b;
	for(int i=0;i<R;++i){
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);
		input[i]=make_pair(a+1,b);
	}
	sort(input,input+R);
	int siz=unique(input,input+R)-input;
	for(int i=0;i<siz;++i)
		++sum[input[i].first],--sum[input[i].second];
	for(int i=1;i<=N;++i){
		sum[i]+=sum[i-1];
		printf("%d\n",H-sum[i]);	
	}
	return 0;
}

