#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct Range final{
	uint32_t l,r,len;
} input[500000];
map<uint32_t,int32_t> sum;
uint32_t n,m;
constexpr auto nil=1U<<30;
int32_t foo(uint32_t p,int32_t num){
	uint32_t i,minv=nil;
	vector<uint32_t> len;
	for(i=0;num;++i)
		if(input[i].l<=p && p<=input[i].r)
			--num,len.emplace_back(input[i].len); 
	sort(len.begin(),len.end());
	for(i=0;i<=len.size()-m;++i)
		minv=min(minv,len[i+m-1]-len[i]);
	return minv;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(uint32_t i=0;i<n;++i){
		auto& x=input[i];
		cin>>x.l>>x.r;
		x.len=x.r-x.l;
		x.l<<=1,x.r<<=1;
		++sum[x.l],--sum[x.r+1];
		sum.insert({x.r,0});
	}
	for(auto iter2=sum.begin(),iter1=iter2++;iter2!=sum.end();iter1=iter2++)
		iter2->second+=iter1->second;
	
	int32_t ans=nil;
	for(auto&& x:sum)
		if(x.second>=m)ans=min(ans,foo(x.first,x.second));
	cout<<(ans==nil?-1:ans)<<endl;
	return 0;
}

