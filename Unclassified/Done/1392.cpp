#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
struct Info{
	int a,b,w;
	Info(){}
	Info(int A,int B,int W):a(A),b(B),w(W){}
	bool operator<(Info rhs) const{
		return w>rhs.w;
	}
};
Info mData[800];
int mSize;
class FastArray{
public:
	typedef Info T;
	typedef T value_type;
	typedef T reference;
	typedef T const_reference;
	typedef int size_type;
	int size() const{
		return mSize;
	}
	bool empty() const{
		return !mSize;
	}
	void push_back(T x){
		mData[mSize++]=x;
	}
	void pop_back(){
		--mSize;
	}
	T* begin(){
		return mData;
	}
	T* end(){
		return mData+mSize;
	}
	T front() const{
		return *mData;
	}
	static void clear(){
		mSize=0;
	}
};
int mat[2][800],line[800];
int main(){
	int n,m,k;
	n=read();
	m=read();
	k=read();
	for(int i=0;i<m;++i)
		mat[0][i]=read();
	std::partial_sort(mat[0],mat[0]+k,mat[0]+m);
	std::priority_queue<Info,FastArray> heap;
	int c=0;
	for(int i=1;i<n;++i){
		FastArray::clear();
		for(int j=0;j<m;++j)
			line[j]=read();
		std::partial_sort(line,line+k,line+m);
		for(int j=0;j<k;++j)
			heap.push(Info(0,j,mat[c][0]+line[j]));
		for(int j=0;j<k;++j){
			Info top=heap.top();
			heap.pop();
			mat[1-c][j]=top.w;
			if(top.a<k-1)
				heap.push(Info(top.a+1,top.b,mat[c][top.a+1]+line[top.b]));
		}
		c=1-c;
	}
	for(int i=0;i<k;++i)
		printf("%d ",mat[c][i]);
	return 0;
}

