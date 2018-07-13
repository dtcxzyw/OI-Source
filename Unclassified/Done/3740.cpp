#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
int A[3001]={},oper[1000][2],map[4000];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    	scanf("%d%d",&oper[i][0],&oper[i][1]);
    memcpy(map,oper,sizeof(oper));
    int siz=m<<1;
    sort(map,map+siz);
    for(int i=1;i<(m<<1);++i)
    	if(map[i]-map[i-1]>1)
    		map[siz++]=map[i]-1;
    sort(map,map+siz);
    siz=unique(map,map+siz)-map;
    for(int i=0;i<m;++i){
    	for(int j=0;j<2;++j)
    		oper[i][j]=lower_bound(map,map+siz,oper[i][j])-map;
    	for(int j=oper[i][0];j<=oper[i][1];++j)
    		A[j]=i+1;
	}    
    set<int> type;
    for(int i=0;i<siz;++i)
    	if(A[i])
    		type.insert(A[i]); 
	printf("%d\n",static_cast<int>(type.size()));
    return 0;
}

