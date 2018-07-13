#include <iostream>
#include <algorithm>
using namespace std;
uint64_t A[51]={};
int main(){
	int n,i,j;
	cin>>n;
	uint64_t x;
	for(i=0;i<n;++i){
		cin>>x;
		for(j=50;j>=0;--j)
			if(x&(1ULL<<j)){
				if(!A[j]){
					A[j]=x;
					break;
				}
				
				x^=A[j];
			}
	}
	
	uint64_t res=0;
	for(i=50;i>=0;--i)
		res=std::max(res,res^A[i]);
	
	cout<<res<<endl;
	return 0;	
}

