#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int A[110000];
int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&A[i]);
	sort(A,A+n);
	char c[4];
	int k;
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		scanf("%s",c);
		if(*c=='a'){
			scanf("%d",&k);
			int p=upper_bound(A,A+n,k)-A;
			memmove(A+p+1,A+p,sizeof(int)*(n-p));
			A[p]=k;
			++n;
		}
		else printf("%d\n",A[(n-1)>>1]);
	}
	return 0;
}

