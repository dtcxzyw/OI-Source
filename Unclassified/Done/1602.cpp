#include <cstdio>
#include <deque>
typedef __int128 bint;
void print(bint x){
    if(x>=10)print(x/10);
    putchar('0'+x%10);
}
bool flag[1001]={};
int main(){
    std::deque<bint,std::vector<bint>,std::greater<bint> > q;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;++i)q.push_back(i);
    while(true){
        bint v=q.front();
        q.pop_front();
        if(v%m==0){
            print(v);
            break;
        }
        if(flag[v%m])continue;
		else flag[v%m]=true;
        for(int i=0;i<n;++i)
            q.push_back(v*10+i); 
    }
    return 0;
}

