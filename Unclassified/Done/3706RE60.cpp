#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
const int size=305,psiz=3501;
struct Node{
    int id,ch[2],fail;	
} T[size*size];
int icnt=1,root=1;
char buf[size];
int insert(int id){
    scanf("%s",buf);
    int p=root;
    for(int i=0;buf[i];++i){
        int c=buf[i]=='T';
        int& nxt=T[p].ch[c];
        if(!nxt)nxt=++icnt;
        p=nxt;
    }
    T[p].id=id;
    return p;
}
int q[size];
void cook(){
    int b=0,e=1;
    q[b]=root;
    while(b!=e){
        int u=q[b++];
        for(int i=0;i<2;++i){
            int v=T[u].ch[i];
            if(v){
                if(u==root)T[v].fail=root;
                else{
                    int p=T[u].fail;
                    while(p && !T[p].ch[i])p=T[p].fail;
                    if(p)T[v].fail=T[p].ch[i];
                    else T[v].fail=root;
                }
                q[e++]=v;
            }
        }
    }
}
double A[psiz][psiz]={},B[psiz]={},ans[psiz]={};
void buildMat(){
    for(int i=1;i<=icnt;++i){
        A[i][i]-=1.0;
        if(T[i].id)continue;
        for(int j=0;j<2;++j){
            int cur=i;
            while(!T[cur].ch[j] && cur!=root)cur=T[cur].fail;
            cur=T[cur].ch[j];
            if(!cur)cur=root;
            A[cur][i]+=0.5;
        }
    }
    memset(A[1],0,sizeof(A[1]));
    for(int i=1;i<=icnt;++i)
        if(T[i].id)
            A[1][i]=1.0;
    B[1]=1.0;
}
void solve(){
    int n=icnt;
    for(int i=1;i<=n;++i){
        int x=i;
        for(int j=i+1;j<=n;++j)
            if(fabs(A[x][i])<fabs(A[j][i]))
                x=j;
        if(x!=i){
            for(int j=i;j<=n;++j)
                std::swap(A[x][j],A[i][j]);
            std::swap(B[x],B[i]);
        }
        for(int j=i+1;j<=n;++j){
            double mul=A[j][i]/A[i][i];
            for(int k=i;k<=n;++k)
                A[j][k]-=A[i][k]*mul;
            B[j]-=B[i]*mul;
        }
    }
    for(int i=n;i>=1;--i){
        double sum=B[i];
        for(int j=i+1;j<=n;++j)
            sum-=ans[j]*A[i][j];
        ans[i]=sum/A[i][i];
    }
}
int nid[size];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        nid[i]=insert(i);
    cook();
    buildMat();
    solve();
    for(int i=1;i<=n;++i)
        printf("%.10lf\n",ans[nid[i]]);
    return 0;
}

