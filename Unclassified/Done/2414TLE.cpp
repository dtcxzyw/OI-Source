#include <cstdio>
#include <string>
#include <vector>
#include <map>
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
const int size=100100;
struct Node{
	int fail,to[26];
	std::vector<int> tag;
} T[size];
int newNode(){
	static int cnt=0;
	return ++cnt;
}
int root;
void insert(int tag,const char* buf){
	int p=root;
	for(int i=0;buf[i];++i){
		int c=buf[i]-'a';
		if(!T[p].to[c])T[p].to[c]=newNode();
		p=T[p].to[c];
	}
	T[p].tag.push_back(tag) ;
}
int q[size];
void cook(){
	int b=0,e=1;
	q[b]=root;
	while(b!=e){
		int u=q[b++];
		for(int i=0;i<26;++i){
			int v=T[u].to[i];
			if(v){
				if(u==root)T[v].fail=root;
				else{
					int p=T[u].fail;
					while(p){
						if(T[p].to[i]){
							T[v].fail=T[p].to[i];
							break;
						}
						p=T[p].fail;
					}
					if(!p)T[v].fail=root;
				}
				q[e++]=v;
			}
		}
	}
}
std::map<int,int> edge[size];
int ans[size]={};
void match(const std::string& str,int id){
	int p=root;
	for(int i=0;i<str.size();++i){
		int c=str[i]-'a';
		while(p!=root && !T[p].to[c])p=T[p].fail;
		if(T[p].to[c]){
			p=T[p].to[c];
			int pc=p;
			while(pc!=root){
				for(int i=0;i<T[pc].tag.size();++i){
					int v=T[pc].tag[i];
					std::map<int,int>::iterator it=edge[id].find(v);
					//printf("%d in %d\n",v,id);
					if(it!=edge[id].end())
						++ans[it->second];
				}
				pc=T[pc].fail;
			}
		}
		else p=root;
	}
}
std::vector<std::string> P;
char buf[size],now[size];
int u[size],v[size];
int main(){
	root=newNode();
	scanf("%s",buf);
	int wp=0;
	for(int i=0;buf[i];++i)
		switch(buf[i]){
			case 'B':--wp;break;
			case 'P':{
				now[wp]='\0';
				insert(P.size(),now);
				P.push_back(now);
			}break;
			default:now[wp++]=buf[i];break;
		}
	cook();
	int m=read();
	for(int i=0;i<m;++i){
		u[i]=read()-1;
		v[i]=read()-1;
		edge[v[i]][u[i]]=i;
	}
	for(int i=0;i<P.size();++i)
		match(P[i],i);
	for(int i=0;i<m;++i)
		printf("%d\n",ans[edge[v[i]][u[i]]]);
	return 0;
}

