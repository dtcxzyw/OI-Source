#include <cstdio>
#include <set>
int stack[50001],cnt=0;
int main(){
	std::set<int> point;
	typedef std::set<int>::iterator iter;
	int n,m;
	scanf("%d%d",&n,&m);
	point.insert(0); 
	point.insert(n+1); 
	char c[2];
	int x;
	for(int i=0;i<m;++i){
		scanf("%s",c);
		if(*c!='R')scanf("%d",&x);
		switch(*c){
		case 'D':point.insert(x),stack[++cnt]=x;break;
		case 'R':point.erase(stack[cnt--]);break;
		case 'Q':{
			iter l=point.lower_bound(x); 
			iter r=point.upper_bound(x);
			if(*l==x)puts("0");
			else{
				--l;
				printf("%d\n",*r-*l-1);
			}
		}break;
		}
	}
	return 0;
}

