#include <cstdio>
int maxv(int a,int b){
    return a>b?a:b;
}
int scan(){
	int cnt=0;
	while(true){
		int c=getchar();
		switch(c){
			case '(':cnt+=scan();break;
			case 'a':++cnt;break;
			case '|':return maxv(cnt,scan());break;
			default:return cnt;break;
		}
	}
	return cnt;
}
int main(){
    printf("%d\n",scan());
    return 0;
}

