#include <cstdio>
#include <queue>
#include <set>
char p[210000],tmp[20];
std::set<int> fp[128];
int main(){
	std::priority_queue<int,std::vector<int>,std::greater<int> > q;
	q.push(1);
	int k,m,cnt=0;
	scanf("%d%d",&k,&m);
	for(int i=0;i<k;++i){
		int v=q.top();q.pop();
		q.push(v<<1|1);
		q.push((v<<2)+5);  
		int c=0;
		while(v){
			tmp[++c]=v%10+'0';
			v/=10;
		}
		for(int j=c;j>0;--j)
			p[cnt++]=tmp[j];	
	}
	p[cnt]='\0';
	puts(p);
	int b=0,e=m;
	for(int i=b;i<=e;++i)
		fp[p[i]].insert(i);
	for(int i=0;i<cnt-m;++i){
		for(int j='9';j>='0';--j){
			std::set<int>::iterator it=fp[j].lower_bound(b);
			if(it!=fp[j].end()){
				b=*it+1,putchar(j);
				break;
			}
		}
		++e;
		fp[p[e]].insert(e); 
	}
	puts("");
	return 0;
}

