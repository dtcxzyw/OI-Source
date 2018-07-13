#include <cstdio>
#include <queue>
char name[100][101],code[21];
std::queue<int> u,d;
bool lock[100]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%s%s",name[i],code);
		switch(*code){
		case 'U':u.push(i);break;
		case 'D':d.push(i);break;
		case 'S':lock[i]=true;break;
		}
	}
	for(int i=0;i<n;++i){
		int x;
		if(lock[i])x=i;
		else{
			if(d.size()){
				x=d.front();
				d.pop();
			}
			else{
				x=u.front();
				u.pop();
			}
		}
		puts(name[x]);
	}
	return 0;
}

