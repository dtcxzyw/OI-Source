#include <cstdio>
const char metaTable[10]={'a','e','i','o','u','A','E','I','O','U'};
char buf[101];
bool alpha(char c){
	return ('a'<=c && c<='z') || ('A'<=c && c<='Z');
}
bool meta(char c){
	for(int i=0;i<10;++i)
		if(c==metaTable[i])
			return true;
	return false;
}
int main(){
	gets(buf);
	char* p=buf;
	int cnt=0,xcnt;
	while(*p){
		if(alpha(*p))putchar('.'),++cnt;
		else putchar(*p);
		++p;
	}
	puts("");
	xcnt=cnt/3.0+0.5;
	p=buf;
	bool flag=false;
	while(*p){
		if(alpha(*p)){
			if(xcnt)putchar(*p),--xcnt;
			else putchar('.'),flag|=meta(*p);
		}
		else putchar(*p);
		++p;
	}
	puts("");
	p=buf;
	if(flag){
		xcnt=cnt/3.0+0.5;
		while(*p){
			if(alpha(*p)){
				if(xcnt)putchar(*p),--xcnt;
				else putchar(meta(*p)?*p:'.');
			}
			else putchar(*p);
			++p;
		}
	}
	else{
		xcnt=cnt/3.0*2.0+0.5;
		while(*p){
			if(alpha(*p)){
				if(xcnt)putchar(*p),--xcnt;
				else putchar('.');
			}
			else putchar(*p);
			++p;
		}
	}
	return 0;
}

