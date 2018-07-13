#include <cstdio>
#include <cctype>
#include <set>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';	
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
inline void print(int x){
	printImpl(x);
	putchar('\n');
}
int getOp(){
	int res=0,c;
	do c=getchar();
	while(!isgraph(c));
	while(isgraph(c)){
		res^=c;
		c=getchar();
	}
	return res;
}
template<typename Iter>
inline Iter prev(Iter it){
	return --it;
}
template<typename Iter>
inline Iter next(Iter it){
	return ++it;
}
inline int iabs(int x){
	return x<0?-x:x;
}
const int ins=23,mg=67,msg=6,size=500010;
std::set<int> S;
typedef std::set<int>::iterator IterS;
std::multiset<int> delta;
inline void add(int a,int b){
	delta.insert(iabs(a-b));
}
inline void erase(int a,int b){
	delta.erase(delta.find(iabs(a-b)));
}
int val[size][2]={};
int main(){
	int n=read();
	int m=read();
	int mgans=1<<30;
	for(int i=1;i<=n;++i){
		int x=read();
		val[i][0]=val[i][1]=x;
		S.insert(x);
		if(i!=1)add(x,val[i-1][1]);
	}
	int ans=1<<30;
	{
		IterS l=S.begin(),r=S.begin();
		++r;
		for(;r!=S.end();l=r++)
			ans=std::min(ans,*r-*l);
	}
	for(int j=0;j<m;++j)
		switch(getOp()){
			case ins:{
				int i=read();
				int k=read();
				//mg
				{
					//pre
					mgans=std::min(mgans,iabs(k-val[i][1]));
					//next and pre-next
					if(i!=n){
						int nxt=val[i+1][0];
						erase(val[i][1],nxt);
						add(k,nxt);
					}
					val[i][1]=k;
				}
				//msg
				if(ans!=0){
					std::pair<IterS,bool> res=S.insert(k);
					if(res.second){
						IterS it=res.first;
						IterS p=prev(it),n=next(it);
						if(p!=S.end())ans=std::min(ans,k-*p);
						if(n!=S.end())ans=std::min(ans,*n-k);
					}
					else ans=0;
				}			
			}break;
			case mg:{
				int res=mgans;
				if(delta.size())res=std::min(*delta.begin(),res);	
				print(res);
			}break;
			case msg:print(ans);break;
		}
	return 0;
}

