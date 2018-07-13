#include <cstdio>
#include <set>
#include <stack>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
int line=0;
void warn1(char c){
	printf("Line %d: variable %c might not have been initialized\n",line,c);
}
void warn1(const std::set<char>& list){
	for(std::set<char>::iterator it=list.begin();it!=list.end();++it)
		warn1(*it);
}
void warn2(){
	printf("Line %d: unreachable code\n",line);
}
struct Info{
	std::set<char> var,ifvar;
	bool broken,ifbroken;
	Info():broken(false),ifbroken(false){}
};
std::stack<Info> st;
char buf[1024];
typedef std::vector<std::string> SV;
SV readLine(){
	SV res;
	if(gets(buf)==0)return res;
	std::stringstream ss;
	ss<<buf;
	while(true){
		std::string str;
		ss>>str;
		if(str.empty())break;
		res.push_back(str);
	}
	return res;
}
bool check(const std::string& rhs){
	return !(rhs.size()==1 && isalpha(rhs[0]) && st.top().var.count(rhs[0])==0);
}
bool read(){
	SV sv=readLine();
	if(sv.empty())return false;
	++line;
	if(sv[0]=="PARAM"){
		Info info;
		for(int i=1;i<sv.size();++i)
			info.var.insert(sv[i][0]);
		st.push(info); 
	}
	else if(sv[0]=="IF"){
		if(st.top().broken)warn2();
		else{
			std::set<char> ws;
			for(int i=1;i<sv.size();++i)
				if(!check(sv[i]))
					ws.insert(sv[i][0]);
			warn1(ws); 
		}
		st.push(st.top()); 
	}
	else if(sv[0]=="ELSE"){
		bool flag=st.top().broken;
		std::set<char> ifvar=st.top().var;
		st.pop();
		st.push(st.top()); 
		st.top().ifbroken=flag;
		st.top().ifvar=ifvar;
	}
	else if(sv[0]=="END"){
		Info old=st.top();
		st.pop();
		st.top().broken|=old.broken&&old.ifbroken;
		if(!old.broken && old.ifbroken){
			for(std::set<char>::iterator it=old.var.begin();it!=old.var.end();++it)
				st.top().var.insert(*it);
		}
		if(!old.ifbroken && old.broken){
			for(std::set<char>::iterator it=old.ifvar.begin();it!=old.ifvar.end();++it)
				st.top().var.insert(*it);
		}
		if(!old.broken && !old.broken)
			for(std::set<char>::iterator it=old.var.begin();it!=old.var.end();++it)
				if(old.ifvar.count(*it))
					st.top().var.insert(*it);
	}
	else if(sv[0]=="RETURN"){
		if(st.top().broken)warn2();
		else if(!check(sv[1]))
				warn1(sv[1][0]);
		st.top().broken=true;
	}
	else{
		if(st.top().broken)warn2();
		else{
			std::set<char> ws;
			for(int i=1;i<sv.size();++i)
				if(!check(sv[i]))
					ws.insert(sv[i][0]);
			warn1(ws);
			st.top().var.insert(sv[0][0]);
		}
	}
	/*
	puts("----------------------");
	printf("deep=%d broken=%s\n",st.size(),st.top().broken?"Y":"N");
	printf("vars:");
	for(std::set<char>::iterator it=st.top().var.begin();it!=st.top().var.end();++it){
		putchar(*it);
		putchar(' ');
	}
	puts("");
	printf("ifvars:");
	for(std::set<char>::iterator it=st.top().ifvar.begin();it!=st.top().ifvar.end();++it){
		putchar(*it);
		putchar(' ');
	}
	puts("\n----------------------");
	*/
	return true;
}
int main(){
	while(read());
	return 0;
}

