#include <cstdio>
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
const int size=200005,mod=998244353,maxk=50,fac=131,bsiz=19260817;
typedef unsigned long long U64;
struct Edge{
    U64 hash;
    int nxt,cnt;
} E[size*100];
int last[bsiz]={},ecnt=0;
void add(U64 hash,int op){
    int buc=hash%bsiz;
    int p=last[buc];
    while(p){
        if(E[p].hash==hash){
            E[p].cnt+=op;
            return;
        }
        else p=E[p].nxt;
    }
    ++ecnt;
    E[ecnt].hash=hash;
    E[ecnt].nxt=last[buc],E[ecnt].cnt=op;
    last[buc]=ecnt;
}
int count(U64 hash){
    int buc=hash%bsiz;
    int p=last[buc];
    while(p){
        if(E[p].hash==hash)return E[p].cnt;
        else p=E[p].nxt;
    }
    return 0;
}
int A[size];
struct Node{
    int pre,nxt;
} L[size];
U64 pf[51];
void modify(int u,int v,int op){
    for(int i=2;i<=maxk;++i){
        int head=v;
        for(int j=1;j<i;++j)
            if(L[head].pre)head=L[head].pre;
            else break;
        int tail=head;
        U64 val=A[tail];
		for(int j=1;j<i;++j){
			tail=L[tail].nxt;
			val=val*fac+A[tail];
		}
		while(head!=v && tail){
			add(val,op);
			val-=A[head]*pf[i-1];
			head=L[head].nxt;
			tail=L[tail].nxt;
			val=val*fac+A[tail];
		}
    }
}
void merge(int u,int v){
    L[u].nxt=v;
    L[v].pre=u;
    modify(u,v,1);
}
void split(int u){
    int v=L[u].nxt;
    modify(u,v,-1);
    L[u].nxt=0;
    L[v].pre=0;
}
const int maxl=10000005;
char buf[maxl];
U64 hash[maxl];
int calc(int k){
    int n=strlen(buf+1);
    long long res=1;
    hash[0]=0;
    for(int i=1;i<=n;++i)hash[i]=hash[i-1]*fac+buf[i]-'0';
    for(int r=k;r<=n && res;++r){
        U64 val=hash[r]-hash[r-k]*pf[k];
        res=res*count(val)%mod;
    }
    return res;
}
int main(){
    int n=read();
    int m=read();
    pf[0]=1;
    for(int i=1;i<=maxk;++i)
        pf[i]=pf[i-1]*fac;
    for(int i=1;i<=n;++i){
        A[i]=read();
        add(A[i],1);
        L[i].pre=0;
        L[i].nxt=0;
    }
    for(int i=0;i<m;++i){
        switch(read()){
            case 1:{
                int u=read();
                int v=read();
                merge(u,v);
                break;
            }
            case 2:{
                split(read());
                break;
            }
            case 3:{
                scanf("%s",buf+1);
                printf("%d\n",calc(read()));
                break;
            }
        }
    }
    return 0;
}

