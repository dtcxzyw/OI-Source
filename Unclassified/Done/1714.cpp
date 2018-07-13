#include <cstdio>
int s[500001],q[500001],b=0,e=0,m;
void push(int i){
	while(e>b && s[i]<s[q[e-1]])--e;
	q[e++]=i;
}
int read(){
	int res=0,c;
	bool flag=false;
	do {
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int main(){
	int n=read(),ans=-1<<30;
	m=read();
	s[0]=0;
	for(int i=1;i<=n;++i)
		s[i]+=s[i-1]+read();
	push(0);
	for(int i=1;i<=n;++i){
		while(i-q[b]>m)++b;
		int ps=s[i]-s[q[b]];
		if(ans<ps)ans=ps;
		push(i);
	}
	printf("%d\n",ans);
	return 0;
}

