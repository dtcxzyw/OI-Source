#include <cstdio>
#include <cstring>
char buf[1024*1024+100];
struct Node{
	int fail,c[26],d;
	bool flag;
} node[250];
int cnt=0;
void insert(){
	int p=0;
	for(int i=0;buf[i];++i){
		int c=buf[i]-'a';
		if(!node[p].c[c]){
			node[p].c[c]=++cnt;
			node[node[p].c[c]].d=node[p].d+1;
		}
		p=node[p].c[c];
	}
	node[p].flag=true;
}
int q[250];
void build(){
	int b=0,e=0;
	for(int i=0;i<26;++i)
		if(node[0].c[i])
			q[e++]=node[0].c[i];
	while(b!=e){
		int u=q[b++];
		for(int i=0;i<26;++i){
			int& v=node[u].c[i];
			if(v)node[v].fail=node[node[u].fail].c[i],q[e++]=v;
			else v=node[node[u].fail].c[i];
		}
	}
}
bool flag[1024*1024+100];
int scan(){
	memset(flag,0,sizeof(flag));
	flag[0]=true;
	int p=0,res=0;
	for(int i=1;buf[i];++i){
		int c=buf[i]-'a';
		p=node[p].c[c];
		for(int pc=p;pc;pc=node[pc].fail)
			if(node[pc].flag){
				flag[i]|=flag[i-node[pc].d];
				if(flag[i]){
					res=i;
					break;
				}
			}
	}
	return res;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%s",buf);
		insert();
	}
	build();
	for(int i=0;i<m;++i){
		scanf("%s",buf+1);
		printf("%d\n",scan());
	}
	return 0;
}

