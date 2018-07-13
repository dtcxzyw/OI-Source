#include <cstdio>
#include <cctype>
const int mod=1000000007;
const char* P="helloworldHELLOWORLD";
char buf[500001],lower[256]={};
int size=0;
void pre(){
	for(int i=0;P[i];++i)
		lower[P[i]]=tolower(P[i]);
}
void read(){
	int c;
	while((c=getchar())!=EOF)
		if(lower[c])
			buf[++size]=lower[c];
}
int dp[11];
//H E L L O W O R L D
//1 2 3 4 5 6 7 8 9 10
void add(int a,int b){
	dp[a]=(dp[a]+dp[b])%mod;
}
int main(){
	pre();
	read();
	dp[0]=1;
	for(int i=1;i<=size;++i){
		switch(buf[i]){
			case 'h':if(++dp[1]==mod)dp[1]=0;break;
			case 'e':add(2,1);break;
			case 'l':{
				add(9,8);
				add(4,3);
				add(3,2);
			}break;
			case 'o':{
				add(7,6);
				add(5,4);	
			}break;
			case 'w':add(6,5);break;
			case 'r':add(8,7);break;
			case 'd':add(10,9);break;
		}
	}
	printf("%d\n",dp[10]);
	return 0;
}

