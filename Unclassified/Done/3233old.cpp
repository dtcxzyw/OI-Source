#include <cstdio>
#include <queue>
#include <cstring>
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
void printImpl(int x){
    if(x>=10)printImpl(x/10);
    putchar('0'+x%10);
}
void print(int x){
    printImpl(x);
    putchar(' ');
}
const int size=300100;
struct Edge{
    int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
struct Info{
    int u,p;
    Info(int id,int root):u(id),p(root){}
    bool operator<(Info rhs) const{
        return u>rhs.u;
    }
};
std::priority_queue<Info> A,B;
int ans[size];
bool flag[size];
void BFS(int n){
    while(true){
        while(A.size()){
            Info u=A.top();
            A.pop();
            for(int i=last[u.u];i;i=E[i].next){
                int v=E[i].to;
                if(!flag[v]){
                    flag[v]=true;
                    ++ans[u.p];
                    B.push(Info(v,u.p)); 
                    if(--n==0)return;
                }
            }
        }
        std::swap(A,B);
    }
}
void clear(std::priority_queue<Info>& c){
    c=std::priority_queue<Info>();
}
int main(){
    int n=read();
    for(int i=1;i<n;++i){
        int u=read();
        int v=read();
        addEdge(u,v);
        addEdge(v,u);
    }
    int q=read();
    for(int i=0;i<q;++i){
        clear(A);
        clear(B);
        memset(ans,0,sizeof(ans));
        memset(flag,0,sizeof(flag));
        int m=read();
        for(int j=0;j<m;++j){
            int u=read();
            A.push(Info(u,j));
            ++ans[j];
            flag[u]=true;
        }
        BFS(n-m);
        for(int j=0;j<m;++j)
            print(ans[j]);
        puts("");
    }
    return 0;
}

