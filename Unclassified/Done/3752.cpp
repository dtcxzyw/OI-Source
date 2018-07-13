#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
char buf[257],name[100][256];
bool isAlpha(int c){
	return ('a'<=c && c<='z') || ('A'<=c && c<='Z'); 
}
void toUpper(){
	int i=0;
	while(buf[i]){
		if(buf[i]<'a' && isAlpha(buf[i]))
			buf[i]+='a'-'A';
		++i;
	}
}
int BKDR(){
	toUpper();
	int res=0;
	for(int i=0;buf[i];++i)
		res=res*131+buf[i];
	//printf("Buf @%s@ hash = %d\n",buf,res);
	return res;
}

int main(){
	freopen("input.txt","r",stdin);
	int n;
	cin>>n;
	std::map<int,int> table;
	for(int i=0;i<n;++i){
		cin>>name[i];
		while(cin.peek()!='\n'){
			cin>>buf;
			table[BKDR()]=i;
			while(cin.peek()==' ')cin.ignore();
		}
	}
	
	while(cin.peek()=='\n')cin.ignore();
	
	while(!cin.eof()){
		int lang=-1;
		while(cin.peek()!='\n'){
			if(cin.eof())return 0;
			cin>>buf;
			if(lang==-1){
				int v=BKDR();
				if(table.count(v))
					lang=table[v];
			}
			while(cin.peek()==' ')cin.ignore();
		}
		while(cin.peek()=='\n')cin.ignore();
		cout<<name[lang]<<endl;
	}
	return 0;
}

