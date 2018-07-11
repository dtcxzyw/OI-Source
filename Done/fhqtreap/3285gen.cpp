#include <cstdio>
#include <set>
int getRand(){
	static int seed=123;
	return (seed*=235)%=1000007;
}
std::set<int> x;
int main(){
	freopen("input.txt","w",stdout);
	int n=400000,m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;++i)
		x.insert(i); 
	for(int i=0;i<m;++i){
		int op=getRand()%4+1;
		if(op==1)op=2;
		switch(op){
			case 1:{
				int y=getRand();
				while(x.count(y))y=getRand();
				printf("1 %d %d\n",*x.begin(),y);
				x.erase(x.begin());
				x.insert(y);  
				break;
			}
			case 2:{
				printf("2 %d\n",*x.begin());
				break;
			}
			case 3:{
				printf("3 %d\n",*x.begin());
				break;
			}
			case 4:{
				printf("3 %d\n",getRand()%n+1);
				break;
			}
		}
	}
	return 0;
}

