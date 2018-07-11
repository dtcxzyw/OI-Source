#include <fstream>
#include <cstdio>
int main(){
	std::ifstream out("out.txt"),stdo("std.txt");
	int line=1;
	while(stdo){
		int a=-1,b=-1;
		out>>a,stdo>>b;
		if(a!=b){
			printf("line %d out:%d stdout:%d\n",line,a,b);
			break;
		}
		++line;
	}
	return 0;
}

