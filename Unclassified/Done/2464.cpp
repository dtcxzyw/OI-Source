#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>
int read(){
    int res=0,c;
    do c=getchar();
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}
int getOp(){
    int c;
    do c=getchar();
    while(c!='C'&&c!='Q');
    return c;
}
const int size=100100;
std::vector<int> list[size*2];
void insert(int k,int x){
	list[k].insert(std::lower_bound(list[k].begin(),list[k].end(),x),x); 
}
void erase(int k,int x){
	list[k].erase(std::lower_bound(list[k].begin(),list[k].end(),x)); 
}
typedef std::vector<int>::iterator IterT;
bool sorted[size*2]={};
int A[size],B[size*2];
int get(int x,int siz){
    return std::lower_bound(B,B+siz,x)-B;
}
struct Operator{
    int op,x,y,k;
} Op[size];
int main(){
    int n=read();
    int m=read();
    int cnt=0;
    for(int i=1;i<=n;++i)
        B[cnt++]=A[i]=read();
    for(int i=0;i<m;++i){
        Op[i].op=getOp();
        if(Op[i].op=='C'){
            Op[i].x=read();
            Op[i].k=read();
        }
        else{
            Op[i].x=read();
            Op[i].y=read();
            Op[i].k=read();
        }
        B[cnt++]=Op[i].k;
    }
    std::sort(B,B+cnt);
    cnt=std::unique(B,B+cnt)-B;
    for(int i=1;i<=n;++i){
        A[i]=get(A[i],cnt);
        list[A[i]].push_back(i);
    }
    for(int i=1;i<=n;++i)
    	if(!sorted[A[i]]){
    		std::sort(list[A[i]].begin(),list[A[i]].end());
    		sorted[A[i]]=true;	
    	}
    for(int i=0;i<m;++i){
        Op[i].k=get(Op[i].k,cnt);
        if(Op[i].op=='C'){
            if(Op[i].k!=A[Op[i].x]){
                erase(A[Op[i].x],Op[i].x);
                A[Op[i].x]=Op[i].k;
                insert(A[Op[i].x],Op[i].x); 
            }
        }
        else{
            std::vector<int>& ref=list[Op[i].k];
            IterT begin=std::lower_bound(ref.begin(),ref.end(),Op[i].x);
            IterT end=std::upper_bound(ref.begin(),ref.end(),Op[i].y);
            int ans=std::distance(begin,end);
            printf("%d\n",ans);
        }
    }
    return 0;
}

