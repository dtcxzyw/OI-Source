#include <cstdio>
bool in[201]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int c;
		scanf("%d",&c);
		while(c){
			in[c]=true;
			scanf("%d",&c);
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		ans+=!in[i];
	printf("%d\n",(ans?ans:1));
	return 0;
}

