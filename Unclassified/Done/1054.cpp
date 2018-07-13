#include <cstdio>
#include <cmath>
const int p=32767;
int clamp(int x){
	return (x%p+p)%p;
}
int powi(int x,int k){
	int res=1;
	while(k){
		if(k&1)res=res*x%p;
		k>>=1,x=x*x%p;
	}
	return res;
}
struct Expr{
	char type;
	int val;
	Expr *l,*r;
	int get(){
		switch(type){
		case 'c':return val;
		case 'a':return 1926;
		case '+':return clamp(l->get()+r->get());
		case '-':return clamp(l->get()-r->get());
		case '*':return clamp(l->get()*r->get());
		case '^':return powi(l->get(),r->get());
		}
	}
};
char buf[60];
Expr* parseExpr(int l,int r){
	Expr* res=new Expr;
	if(l==r && buf[l]=='a'){
		res->type='a';
		return res;
	}
	bool c=true;
	res->val=0;
	for(int i=l;i<=r;++i)
		if('0'<=buf[i]&&buf[i]<='9')
			res->val=res->val*10+buf[i]-'0';
		else{
			c=false;
			break;
		}
	if(c){
		res->type='c';
		return res;
	}
	int d=0;
	for(int i=r;i>=l;--i)
		switch(buf[i]){
			case '(':++d;break;
			case ')':--d;break;
			case '+':
			case '-':if(d==0){
				res->type=buf[i];
				res->l=parseExpr(l,i-1),res->r=parseExpr(i+1,r);
				return res;
			}break;
		}
		
	d=0;
	for(int i=r;i>=l;--i)
		switch(buf[i]){
			case '(':++d;break;
			case ')':--d;break;
			case '*':if(d==0){
				res->type='*';
				res->l=parseExpr(l,i-1),res->r=parseExpr(i+1,r);
				return res;
			}break;
		}
		
	d=0;
	for(int i=r;i>=l;--i)
		switch(buf[i]){
			case '(':++d;break;
			case ')':--d;break;
			case '^':if(d==0){
				res->type='^';
				res->l=parseExpr(l,i-1),res->r=parseExpr(i+1,r);
				return res;
			}break;
		}
		
	while(buf[l]=='('&&buf[r]==')')++l,--r;
	return parseExpr(l,r);
}
bool in(int c){
	if('0'<=c&&c<='9')return true;
	switch(c){
	case ' ':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')':
	case 'a':return true;
	}
	return false;
}
Expr* readExpr(){
	int len=0,c,d=0;
	bool check=true;
	do c=getchar();
	while(!in(c));
	int last=-1;
	while(in(c)){
		if(c!=' '){
			buf[len++]=c;
			if(c=='(')++d,last=len;
			else if(c==')'){
				--d;
				if(d<0 || len==last+1)check=false;
			}
		}
		c=getchar();
	}
	buf[len]='\0';
	check&=(d==0);
	return check?parseExpr(0,len-1):0;
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
bool check(Expr* a,Expr* b){
	if(a&&b) return a->get()==b->get();
	return false;
}
bool flag[30]={};
int main(){
	Expr* P=readExpr();
	int n=read();
	for(int i=0;i<n;++i){
		Expr* Q=readExpr();
		if(check(P,Q))flag[i]=true;
	}
	for(int i=0;i<n;++i)
		if(flag[i])putchar('A'+i);
	return 0;
}

