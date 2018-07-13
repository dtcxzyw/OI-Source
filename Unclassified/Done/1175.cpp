#include <cstdio>
#include <cstring>
int ipow(int a,int b){
	int res=1;
	while(b--)res*=a;
	return res;
}
struct Operator{
	char type;
	Operator *l,*r;
	int value;
	bool flag;
	void calc(){
		if(l->flag&&r->flag){
			switch(type){
				case '+':value=l->value+r->value;break;
				case '-':value=l->value-r->value;break;
				case '*':value=l->value*r->value;break;
				case '/':value=l->value/r->value;break;
				case '^':value=ipow(l->value,r->value);break;
			}
			flag=true;
		}
		else if(l->flag)r->calc();
		else l->calc();
	}
	
	void print() const{
		if(flag) printf("%d",value);
		else{
			l->print();
			putchar(' ');
			r->print();
			putchar(' ');
			putchar(type);
		}
	}
};
char buf[256];
Operator* scan(int l,int r){
	Operator* node=new Operator;
	if(l==r){
		node->flag=true;
		node->value=buf[l]-'0';
		return node;
	}
	int p=0;
	node->flag=false;
	for(int i=r;i>=l;--i)
		switch(node->type=buf[i]){
		case '(':++p;break;
		case ')':--p;break;
		case '+':
		case '-':if(p==0){
					node->l=scan(l,i-1);
					node->r=scan(i+1,r);
					return node;
				}break;
		}

	p=0;

	for(int i=r;i>=l;--i)
		switch(node->type=buf[i]){
		case '(':++p;break;
		case ')':--p;break;
		case '*':
		case '/':if(p==0){
					node->l=scan(l,i-1);
					node->r=scan(i+1,r);
					return node;
				}break;
		}
	
	p=0;
	
	for(int i=r;i>=l;--i)
		switch(node->type=buf[i]){
		case '(':++p;break;
		case ')':--p;break;
		case '^':if(p==0){
					node->l=scan(l,i-1);
					node->r=scan(i+1,r);
					return node;
				}break;
		}
	delete node;
	return scan(l+1,r-1);
}
const char* table="0123456789+-*/^()";
int main(){
	gets(buf);
	int cnt=0;
	for(int i=0;buf[i];++i)
		for(int j=0;table[j];++j)
			if(buf[i]==table[j])
				buf[cnt++]=buf[i];
	buf[cnt]='\0'; 
	Operator *root=scan(0,strlen(buf)-1);
	root->print();
	puts("");
	while(!root->flag){
		root->calc();
		root->print();
		puts("");
	}
	return 0;
}

