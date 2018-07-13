#include <cstdio>
#include <deque>
int getOp(){
	int res,c;
	do c=getchar();
	while(c<'A'||c>'Z');
	res=c;
	while('A'<=c&&c<='Z')c=getchar();
	return res;
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
char buf[3*(1<<20)];
void readStr(int siz){
	int c;
	for(int i=0;i<siz;++i){
		do c=getchar();
		while(c<32||c>126);
		buf[i]=c;
	}	
}
std::deque<char> S;
typedef std::deque<char>::iterator IterT;
int main(){
	int n=read();
	int p=0;
	for(int i=0;i<n;++i){
		int op=getOp();	
		switch(op){
			case 'M':p=read();break;
			case 'I':{
				int siz=read();
				readStr(siz);
				S.insert(S.begin()+p,buf,buf+siz); 
			}break;
			case 'D':{
				IterT begin=S.begin()+p;
				S.erase(begin,begin+read());
			}break;
			case 'G':{
				int siz=read();
				IterT ptr=S.begin()+p;
				for(int i=0;i<siz;++i,++ptr)
					putchar(*ptr);
				putchar('\n');
			}break;
			case 'P':--p;break;
			case 'N':++p;break;
		}
	}
	return 0;
}

