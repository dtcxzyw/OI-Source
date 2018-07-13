#include <cstdio>
#include <cstring>
bool flag[256]={};
char sta[256];
int cp[200]={};
int add(int x,int off){
	if(x==-1)return -1;
	return x+off;
}
void foo(){
	memset(flag,0,sizeof(flag));
	int n;
	char buf[20],op[20],var[20],b[20],e[20];
	scanf("%d %s",&n,buf);
	int match;
	if(buf[2]=='1')match=0;
	else sscanf(buf+4,"%d",&match);
	int top=0,ans=0;
	bool err=false;
	for(int i=0;i<n;++i){
		scanf("%s",op);
		if(*op=='F'){
			scanf("%s %s %s",var,b,e);
			if(!err){
				++top;
				sta[top]=*var;
				int l,r;
				if(*b=='n')l=1000;
				else sscanf(b,"%d",&l);
				if(*e=='n')r=1000;
				else sscanf(e,"%d",&r);
				if(l>r)cp[top]=-1;
				else if(l==r)cp[top]=add(cp[top-1],0);
				else if(r==1000)cp[top]=add(cp[top-1],1);
				else cp[top]=add(cp[top-1],0);
				if(flag[*var])err=true;
				else flag[*var]=true;
			}
		}
		else if(!err){
			if(ans<cp[top])ans=cp[top];
			flag[sta[top]]=false;
			--top;
			if(top<0)err=true;
		}
	}
	if(top!=0)err=true;
	if(err)puts("ERR");
	else puts(ans==match?"Yes":"No");
}
int main(){
	freopen("complexity.in","r",stdin);
	freopen("complexity.out","w",stdout);
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)foo();
	return 0;
}

