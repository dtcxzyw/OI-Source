#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

char buf[1000001];

struct Word final{
	string str;
	int id;
	bool operator<(const Word& rhs) const{
		return str<rhs.str;
	}
	
	int test(int p) const{
		return p<str.size()?buf[p]-str[p]:1;
	}
} words[30001];

inline int find(int l,int r,int p,bool first){
	int mid,res,ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		res=words[mid].test(p);
		if(res==0){
			ans=mid;
			if(first)r=mid-1;
			else l=mid+1;
		}
		else if(res>0)l=mid+1;
		else r=mid-1;
	}
	return ans;
}

int main(){
	int w,n,i,j;
	scanf("%d%d",&w,&n);
	for(i=1;i<=w;++i){
		scanf("%s",buf);
		words[i].str=buf;
		words[i].id=i;
	}
	sort(words,words+w);
	int l,r,k,s,mid,res;
	for(i=0;i<n;++i){
		scanf("%d%s",&j,buf);
		--j;
		l=1,r=w,k=0,s=strlen(buf);
		while(r>l+j && k<s){
			l=find(l,r,k,true);
			if(l==-1)break;
			r=find(l,r,k,false);
			if(r==-1)break;
			++k;
		}
		printf("%d\n",(k==s && words[l+j].str.size()>=s
		 && words[l+j].str.substr(0,s)==buf)?words[l+j].id:-1);
	}
	
	return 0;
}

