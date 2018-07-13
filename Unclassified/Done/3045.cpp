#include <cstdio>
#include <algorithm>
const int size=50000;
bool flag=true;
struct Cow{
	int p,c;
	bool operator<(Cow rhs) const{
		if(flag)return c<rhs.c;
		else return p<rhs.p;
	}
} cow[size];
int main(){
	int n,k;
	long long m;
	scanf("%d%d%lld",&n,&k,&m);
	for(int i=0;i<n;++i)
		scanf("%d%d",&cow[i].p,&cow[i].c);
	std::sort(cow,cow+n);
	for(int i=0;i<k;++i)
		if(m>=cow[i].c)
			m-=cow[i].c;
		else{
			printf("%d\n",i);
			return 0;
		}
	std::sort(cow+k,cow+n);
	for(int i=k;i<n;++i)
		if(m>=cow[i].p)m-=cow[i].p;
		else{
			printf("%d\n",i);
			return 0;
		}
	printf("%d\n",n);
	return 0;
}

