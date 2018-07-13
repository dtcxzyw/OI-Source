#include <cstdio>
#include <cstring>
#include <queue>
#include <functional>
int num[200001];
int read(){
	int res=0,c;
	bool flag=false;
	do {
		c=getchar();
		flag|=c=='-';
	}while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
class FastArray{
private:
	int mArray[200001],mSize;
public:
	typedef int value_type;
	typedef int size_type;
	typedef int const_reference;
	typedef int reference;
	FastArray():mSize(0){}
	int size() const {
		return mSize;
	}
	bool empty() const{
		return !mSize;
	}
	int* begin(){
		return mArray;
	}
	int* end(){
		return mArray+mSize;
	}
	int front() const{
		return *mArray;
	}
	void push_back(int x){
		mArray[mSize]=x;
		++mSize;
	}
	void pop_back(){
		--mSize;
	}
};
std::priority_queue<int,FastArray> l;
std::priority_queue<int,FastArray,std::greater<int> > r;
int main(){
    int n,m;
    n=read();
    m=read();
    for(int i=1;i<=n;++i)
    	num[i]=read();
    int p=1,e;
    for(int i=1;i<=m;++i){
    	e=read();
    	for(;p<=e;++p){
    		l.push(num[p]);
    		if(l.size()==i)r.push(l.top()),l.pop();
    	}
		printf("%d\n",r.top());
		l.push(r.top());
		r.pop();
    }
    return 0;
}

