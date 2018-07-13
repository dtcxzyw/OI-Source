#include <cstdio>
#include <string>
using namespace std;
bool test(const string& str){
	for(int i=0;i<str.size();++i)
		if(str[i]!='0')
			return false;
	return true;	
}
void outUnit(string num,int& cnt,string& out){
	if(test(num))out.push_back('0');
	else{
		const char* base="SBQ";
		while(num.size()){
			if(num[0]=='0'){
				while(num.size() && num[0]=='0')num.erase(num.begin());
				if(num.size())out.push_back('0');
			}
			else{
				out.push_back(num[0]);
				if(num.size()>1)out.push_back(base[num.size()-2]);
				num.erase(num.begin());
			}
		}
		
		if(cnt){
			const char* level="WY";
			out.push_back(level[cnt-1]);
		}
	}
	--cnt;
}
void out(string num){
	while(num.size() && num[0]=='0')num.erase(num.begin());
	if(num.empty()){
		putchar('0');
		return;
	}
	string out;
	int cnt=(num.size()-1)/4;
	if(num.size()%4){
		outUnit(num.substr(0,num.size()%4),cnt,out);
		num.erase(num.begin(),num.begin()+num.size()%4);
	}
	for(int i=0;i<num.size()/4;++i)
		outUnit(num.substr(i*4,4),cnt,out);
	
	while(*out.rbegin()=='0')out.erase(out.size()-1);
	
	char last='\0';
	for(int i=0;i<out.size();++i)
		if(out[i]!=last)
			putchar(last=out[i]);
}
int main(){
	bool inFloat=false;
	int c=getchar();
	std::string num,fp;
	while(c!=EOF && c!='\n' && c!=' '){
		if(c=='-')putchar('F');
		else if(c=='.')inFloat=true;
		else if('0'<=c && c<='9'){
			if(inFloat)fp.push_back(c);
			else num.push_back(c);
		}
		c=getchar();
	}
	out(num);
	if(fp.size())printf("D%s",fp.c_str());
	return 0;
}

