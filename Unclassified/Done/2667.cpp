#include <cstdio>
int prime[10000],cnt=1;
bool test(int x){
	if(x==1)return false;
	for(int i=0;i<cnt && x>prime[i];++i)
		if(x%prime[i]==0)return false;
	return true;
}
void pre(){
	prime[0]=2;
	for(int i=3;i<=10000;i+=2)
		if(test(i))prime[cnt++]=i;
}
int vec[100000];
int main(){
	pre();
	int n,p=0,siz=1;
	vec[0]=0;
	scanf("%d",&n);
	if(n>2)vec[siz++]=2;
	while(p<siz){
		int u=vec[p++];
		u*=10;
		for(int i=1;i<=9;i+=2)
			if(u+i<n && test(u+i))
				vec[siz++]=u+i;  
	}
	printf("%d\n",siz-1);
	for(int i=1;i<siz;++i)
		printf("%d\n",vec[i]);
	return 0;
}


