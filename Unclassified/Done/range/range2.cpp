#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
struct Range final{
	uint32_t l,r,len;
} input[500000];
map<uint32_t,uint32_t> num;
vector<int32_t> sum[1000000];
uint32_t n,m;
constexpr auto nil=1U<<30;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(uint32_t i=0;i<n;++i){
		auto& x=input[i];
		cin>>x.l>>x.r;
		x.len=x.r-x.l;
		x.l<<=1,x.r<<=1;
		num[x.l]=num[x.r]=0;
	}
	uint32_t cnt=0;
	for(auto&& x:num)
	{
		x.second=cnt;
		++cnt;
	}
	
	for(uint32_t i=0;i<n;++i)
		for(uint32_t j=num[input[i].l];j<=num[input[i].r];++j)
			sum[j].emplace_back(input[i].len);
	
	int32_t ans=nil;
	for(uint32_t i=0;i<cnt;++i)
		if(sum[i].size()>=m)
		{
			auto& len=sum[i];
			sort(len.begin(),len.end());
			for(uint32_t j=0;j<=len.size()-m;++j)
				ans=min(ans,len[j+m-1]-len[j]);
		}
	cout<<(ans==nil?-1:ans)<<endl;
	return 0;
}

