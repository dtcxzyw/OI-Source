#include <cstdio>
#include <cstring>
#include <vector>
char P[201];
int next[201];
char buf[201];
std::vector<char> cache;
long long num=0;
inline char get(int i){
	if(cache.size()<=i){
		++num;
		sprintf(buf,"%lld",num);
		int len=strlen(buf);
		cache.resize(cache.size()+len);
		memcpy(cache.data()+cache.size()-len,buf,len);
	}
	return cache[i];
}
int main(){
	cache.reserve(1U<<26); 
	scanf("%s",P);
	const int len=strlen(P);
	int i,j=0;
	next[0]=next[1]=0;
	for(i=1;i<len;++i){
		while(j&&P[i]!=P[j])j=next[j];
		j+=P[i]==P[j];
		next[i+1]=j;
	}
	i=j=0;
	char c;
	while(true){
		c=get(i);
		while(j&&c!=P[j])j=next[j];
		j+=c==P[j];
		if(j==len){
			printf("%d\n",i-j+2);
			return 0;
		}
		++i;
	}
	return 0;
}

