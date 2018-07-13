#include <cstdio>
#include <queue>
const int size=100001;
int A[size],B[size];
struct Node{
	int v,a,b;
	bool operator<(const Node& rhs) const{
		return v>rhs.v;
	}
};
std::priority_queue<Node> heap;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&A[i]);
	for(int i=0;i<n;++i){
		scanf("%d",&B[i]);
		heap.push(Node{A[0]+B[i],0,i});
	}
	
	for(int i=0;i<n;++i){
		Node minv=heap.top();
		heap.pop();
		printf("%d ",minv.v);
		heap.push(Node{A[minv.a+1]+B[minv.b],minv.a+1,minv.b});
	}
	
	return 0;
}

