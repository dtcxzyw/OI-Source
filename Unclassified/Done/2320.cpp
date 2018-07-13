#include <cstdio>
#include <set>
int main(){
	int m;
	scanf("%d",&m);
	std::multiset<int> A;
	while(m){
		A.insert((m+1)>>1);
		m>>=1;
	}
	printf("%d\n",static_cast<int>(A.size()));
	for(std::multiset<int>::iterator it=A.begin();it!=A.end();++it)
		printf("%d ",*it);
	return 0;
}

