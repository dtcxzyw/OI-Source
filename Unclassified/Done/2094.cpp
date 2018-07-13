#include <cstdio>
#include <queue>
int main(){
	int n,k,x;
	scanf("%d%d",&n,&k);
	std::priority_queue<int> heap;
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		heap.push(x);
	}
	while(heap.size()>1){
		int t1=heap.top();heap.pop();
		int t2=heap.top();heap.pop();
		heap.push((t1+t2)/k); 
	}
	printf("%d\n",heap.top());
	return 0;
}

