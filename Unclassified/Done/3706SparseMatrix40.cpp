#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
const int size=305,psiz=size*size;
struct Node{
    int id,ch[2],fail;	
} T[psiz];
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
typedef std::map<int,double> Map;
typedef Map::iterator IterM;
Map A[psiz];
typedef std::set<int> Set;
typedef Set::iterator IterS;
Set pos[psiz];
double B[psiz]={},ans[psiz]={};
int nid[size];
void buildMat(int n){
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
    A[1].clear();
    for(int i=1;i<=n;++i)
    	A[1][nid[i]]=1.0;
    B[1]=1.0;
    for(int i=1;i<=icnt;++i)
    	for(IterM it=A[i].begin();it!=A[i].end();++it)
    		pos[it->first].insert(i); 
}
void solve(){
    int n=icnt;
    for(int i=1;i<=n;++i){
        int x=i;
        for(IterS j=pos[i].lower_bound(i+1);j!=pos[i].end();++j)
        	if(fabs(A[x][i])<fabs(A[*j][i]))
        		x=*j;
        if(x!=i){
            A[x].swap(A[i]);
            for(IterM j=A[i].lower_bound(i);j!=A[i].end();++j)pos[j->first].insert(i);
            for(IterM j=A[x].lower_bound(i);j!=A[x].end();++j)pos[j->first].insert(x);
            std::swap(B[x],B[i]);
        }
        for(IterS j=pos[i].lower_bound(i+1);j!=pos[i].end();++j){
        	int vj=*j;
            double mul=A[vj][i]/A[i][i];
            for(IterM k=A[i].lower_bound(i);k!=A[i].end();++k){
                A[vj][k->first]-=k->second*mul;
                if(k->first!=i)pos[k->first].insert(vj);
            }
            B[vj]-=B[i]*mul;
        }
    }
    for(int i=n;i>=1;--i){
        double sum=B[i];
        for(IterM j=A[i].lower_bound(i+1);j!=A[i].end();++j)
            sum-=ans[j->first]*j->second;
        ans[i]=sum/A[i][i];
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        nid[i]=insert(i);
    cook();
    buildMat(n);
    solve();
    for(int i=1;i<=n;++i)
        printf("%.10lf\n",ans[nid[i]]);
    return 0;
}

