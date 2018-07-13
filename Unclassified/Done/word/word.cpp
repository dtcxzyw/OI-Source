#include <cstdio>
char str[100000];
int cnt=0;
int main(){
	int n,x;
	scanf("%d\n",&n);
	char c[2]={};
	for(int i=0;i<n;++i){
		scanf("%s",c);
		switch(*c){
			case 'T':{
				scanf("%s",c);
				str[cnt]=*c;
				++cnt;
			}break;
			case 'U':{
				scanf("%d",&x);
				cnt-=x;
			}break;
			case 'Q':{
				scanf("%d",&x);
				printf("%c\n",str[x-1]);
			}break;
		}
	}
	return 0;
}

