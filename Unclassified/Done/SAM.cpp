#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=1000001;
class SAM{
private:
	struct State{
		int len=0,link=0,next[26]={};
	} st[size<<1];
	char buf[size];
	int psiz[size<<1]={},cnt[size<<1]={},order[size<<1];
	int siz,last;
	long long ans=0;
	void insert(int c){
		int now=++siz;
		st[now].len=st[last].len+1;
		int p;
		for(p=last;p && !st[p].next[c];p=st[p].link)
			st[p].next[c]=now;
		if(!p)st[now].link=1;
		else{
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)
				st[now].link=q;
			else{
				int clone=++siz;
				memcpy(st[clone].next,st[q].next,sizeof(int)*26);
				st[clone].len=st[p].len+1,st[clone].link=st[q].link;
				for (;st[p].next[c]==q; p=st[p].link)  
            		st[p].next[c] = clone;
				st[q].link=st[now].link=clone;
			}
		}
		last=now;
		psiz[now]=1;
	}
public:
	SAM():siz(1),last(1){}
	void build(){
		scanf("%s",buf);
		for(int i=0;buf[i];++i)
			insert(buf[i]-'a');
	}
	void work(){
		for(int i=1;i<=siz;++i)++cnt[st[i].len];
		for(int i=1;i<=siz;++i)cnt[i]+=cnt[i-1];
		for(int i=1;i<=siz;++i)order[cnt[st[i].len]--]=i;
		for(int i=siz;i>=1;--i){
			int x=order[i];
			psiz[st[x].link]+=psiz[x];
			if(psiz[x]>1)ans=std::max(ans,1LL*st[x].len*psiz[x]);
		}
		printf("%lld\n",ans);
	}
} sam;
int main(){
	sam.build();
	sam.work();
	return 0;
}

