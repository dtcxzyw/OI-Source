#include <cstdio>
#include <map>
#include <iterator>
using namespace std;
int main(){
    map<int,int> tree;
    int n,op,x;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d%d",&op,&x);
        switch(op){
            case 1:++tree[x];break;
            case 2:{
            	auto iter=tree.find(x);
            	if(iter->second>1)--iter->second;
            	else tree.erase(iter);
			}break;
            case 3:{
				auto iter=tree.find(x);
				int ans=1;
				for(auto i=tree.begin();i!=iter;++i)
					ans+=i->second;
				printf("%d\n",ans);
			}break;
            case 4:{
                for(auto&& p:tree){
                    x-=p.second;
                	if(x<=0){
                		printf("%d\n",p.first);
                		break;
					}
				}
            }break;
            case 5:
            {
                auto iter=tree.lower_bound(x);
                if(iter->first>x || tree.find(x)!=tree.end())--iter;
				printf("%d\n",iter->first);
            }break;
            case 6:printf("%d\n",tree.upper_bound(x)->first);break;
        }
    }
    return 0;
}

