#include <cstdio>
#include <map>
#include <sstream>
#include <string>
using namespace std;
void out(const string& str){
	for(int i=0;i<str.size();++i){
		if(i && i%76==0)putchar('\n');
		putchar(str[i]);
	}
	putchar('\n');
}
int main(){
	map<int,int> mod;
	stringstream buf;
	string str;
	int a,b;
	scanf("%d%d",&a,&b);
	buf<<a/b<<'.';
	a%=b;
	mod[a]=0;
	while(true){
		a*=10;
		int v=a/b,m=a%b;
		if(m && mod.count(m)){
			str.insert(mod[m],1,'(');
			str.push_back('0'+v);
			str.push_back(')');
			buf<<str;
			break;
		}
		else mod[m]=str.size()+1;
		str.push_back('0'+v);
		a%=b;
		if(a==0){
			buf<<str;
			break;
		}
	}
	out(buf.str());
	return 0;
}

