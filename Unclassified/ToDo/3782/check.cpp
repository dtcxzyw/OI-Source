#include <string>
#include <cstdlib>
#include <sstream>
std::string getName(int id){
	std::stringstream ss;
	ss<<"sort"<<id;
	return ss.str();
}
int main(){
	for(int i=1;i<=8;++i){
		std::string name=getName(i);
		std::string in=name+".in";
		std::string out=name+".out";
		std::string cmd1="3782 <"+in+" >"+out;
		system(cmd1.c_str());
		std::string cmd2="checker "+in+" "+out+" "+out;
		system(cmd2.c_str());
	}
	return 0;
}

