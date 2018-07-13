#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
const int sc=1000000;
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int getAlpha(){
	int c;
	do c=getchar();
	while(c<'a'||c>'z');
	return c;
}
int getOp(){
	int c;
	do c=getchar();
	while(c!='+'&&c!='-');
	return c;
}
std::string toString(int x){
	std::stringstream ss;
	ss<<x;
	return ss.str();
}
int var[15];
struct Number{
	int val;
	bool isVar;
	void read(int ch){
		isVar=(ch=='v');
		val=::read();
	}
	void read(){
		read(getAlpha());
	}
	int& get(){
		return isVar?var[val]:val;
	}
};
struct Operator{
	int type;
	Number n1,n2;
	int p1,p2;
	int run(int pc,bool* flags,int& cnt){
		switch(type){
			case 0:{
				n1.get()+=n2.get();
				return pc+1;
			}
			case 1:{
				n1.get()-=n2.get();
				return pc+1;
			}
			case 2:{
				return flags[cnt++]?p1:p2;
			}
			case 3:{
				return n1.get()<n2.get()?p1:p2;
			}
		}
	}
} op[36000];
int p=0,n;
void build(){
	n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		int c=getAlpha();
		switch(c){
			case 'i':{
				op[i].type=3;
				op[i].n1.read();
				op[i].n2.read();
				op[i].p1=read();
				op[i].p2=read();
				break;
			}
			case 's':{
				++p;
				op[i].type=2;
				op[i].p1=read();
				op[i].p2=read();
				break;
			}
			default:{
				op[i].n1.read(c);
				op[i].type=(getOp()=='-');
				op[i].n2.read();
			}
		}
	}
}
const int size=1000005;
struct Res{
	bool flag[size];
	int cnt;
	void gen(){
		for(int i=0;i<size;++i)
			flag[i]=rand();
	}
	void build(){
		for(int i=1;i<=5;++i){
			unsigned int r1=rand();
			unsigned int r2=rand();
			int p=r1*r2%(cnt+1);
			flag[p]^=1;
		}
	}
	void print(){
		for(int i=0;i<cnt;++i)
			puts(flag[i]?"1":"2");
	}
};
int run(Res& input){
	memset(var,0,sizeof(var));
	int pc=1,cnt=0;
	while(1<=pc && pc<=n && cnt<size)
		pc=op[pc].run(pc,input.flag,cnt); 
	input.cnt=cnt; 
	return var[1];
}
Res cur,bak,maxwell;
int main(){
	std::string id=toString(read());
	freopen(("train"+id+".in").c_str(),"r",stdin);
	srand(clock());
	build();
	int maxv,lv;
	for(int i=0;i<p;++i)cur.flag[i]=rand()&1;
	cur.cnt=p;
	maxwell=cur;
	maxv=lv=run(cur);
	clock_t beg=clock();
	for(int i=0;i<sc;++i){
		bak=cur;
		cur.build();
		int cv=run(cur);
		if(cv<lv)cur=bak;
		else lv=cv;
		if(cv>maxv){
			maxwell=cur;
			maxv=cv;
		}
		if((i&1023)==1){
			double ratio=1.0*i/sc;
			int t=(clock()-b)/CLOCK_PER_SEC;
			int remain=t/ratio;
			int s=remain%60;
			remain/=60;
			int m=remain%60;
			remain/=60;
			int h=remain;
			printf("%.2lf % %d h %d min %d s\n",ratio*100.0,h,m,s);
		}
	}
	freopen(("train+"id+".out").c_str(),"w",stdout);
	maxwell.print();
	return 0;
}

