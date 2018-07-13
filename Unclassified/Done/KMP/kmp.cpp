#include <cstdio>
#include <cstring>
char s1[1000001],s2[1001];
int next[1001];
using namespace std;
int main(){
	scanf("%s%s",s1,s2);
	const int len1=strlen(s1),len2=strlen(s2);
	int i,j=0;
	next[0]=next[1]=0;
	for(i=1;i<len2;++i){
		while(j&&s2[i]!=s2[j])j=next[j];
		j+=s2[i]==s2[j];
		next[i+1]=j;
	}
	j=0;
	for(i=0;i<len1;++i){
		while(j&&s1[i]!=s2[j])j=next[j];
		j+=s1[i]==s2[j];
		if(j==len2){
			printf("%d\n",i-j+2);
			j=next[j];
		}
	}
	for(i=1;i<=len2;++i)
		printf("%d ",next[i]);
	return 0;	
}

