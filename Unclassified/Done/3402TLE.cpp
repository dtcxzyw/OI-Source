#include <cstdio>
#include <vector>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
struct Info{
	int fa,t;
	Info(int p,int tv):fa(p),t(tv){}
	bool operator<(Info rhs) const{
		return t<rhs.t;
	}
};
const int size=100005;
std::vector<Info> info[size];
int now=0;
int getFa(int u){
	return (std::upper_bound(info[u].begin(),info[u].end(),Info(0,now))-1)->fa;
}
void setFa(int u,int p,int t){
	info[u].push_back(Info(p,t));
}
int find(int u){
	int fa=getFa(u);
	return fa==u?u:find(fa);
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)setFa(i,i,0);
	for(int i=1;i<=m;++i)
		switch(read()){
			case 1:{
				int fu=find(read()),fv=find(read());
				if(fu!=fv)setFa(fu,fv,i),now=i;
			}break;
			case 2:{
				now=read();
			}break;
			case 3:{
				puts(find(read())==find(read())?"1":"0");
			}break;
		}
	return 0;
}

