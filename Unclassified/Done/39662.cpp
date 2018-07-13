#include <cstdio>
const int size=1001000,strsiz=210;
char buf[size];
struct Node{int fail,next[26],sum;} tree[size];
int end[strsiz],q[size];
int main(){
	int n;
	scanf("%d",&n);
	int cnt=1;
	for(int i=1;i<=n;++i){
		scanf("%s",buf);
		int p=1;
		for(int j=0;buf[j];++j){
			int c=buf[j]-'a';
			if(!tree[p].next[c])tree[p].next[c]=++cnt;
			p=tree[p].next[c];
			++tree[p].sum;
		}
		end[i]=p;
	}
	int b=0,e=1;
	q[b]=1;
	while(b!=e){
		int u=q[b++];
		for(int i=0;i<26;++i){
			int v=tree[u].next[i];
			if(v){
				if(u==1)tree[v].fail=1;
				else{
					int p=tree[u].fail;
					while(p){
						if(tree[p].next[i]){
							tree[v].fail=tree[p].next[i];
							break;
						} 
						p=tree[p].fail;
					}
					if(!tree[v].fail)tree[v].fail=1;
				}
				q[e++]=v;
			}
		}
	}
	for(int i=e;i>=1;--i)tree[tree[q[i]].fail].sum+=tree[q[i]].sum;
	for(int i=1;i<=n;++i)printf("%d\n",tree[end[i]].sum);
	return 0;
}

