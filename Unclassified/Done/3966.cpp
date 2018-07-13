#include <cstdio>
#include <vector>
const int size=1001000,strsiz=210;
char buf[size];
const char* begin[strsiz];
struct Node{
    Node *fail,*next[26];
    std::vector<int> sum;
} pool[size];
Node* newNode(){
    static int now=0;
    ++now;
    pool[now].fail=0;
    for(int i=0;i<26;++i)pool[now].next[i]=0;
    return pool+now;
}
void read(int i){
    static int cnt=0;
    int c;
    do c=getchar();
    while(c<'a'||c>'z');
    begin[i]=buf+cnt;
    while('a'<=c&&c<='z'){
        buf[cnt++]=c;
        c=getchar();
    }
    buf[cnt++]='z'+1;
    buf[cnt+1]='\0';
}
Node* root;
void build(int id,const char* str){
    Node* p=root;
    for(int i=0;str[i]!='z'+1;++i){
        int c=str[i]-'a';
        if(p->next[c]==0)p->next[c]=newNode();
        p=p->next[c];
    }
    p->sum.push_back(id);
}
Node* q[size];
void pre(){
    int b=0,e=1;
    q[b]=root;
    while(b<e){
        Node* u=q[b++];
        for(int i=0;i<26;++i){
            Node* v=u->next[i];
            if(v){
                if(u==root)v->fail=root;
                else{
                    Node* p=u->fail;
                    while(p){
                        if(p->next[i]){
                            v->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(v->fail==0)v->fail=root;
                }
                q[e++]=v;
            }
        }
    }
}
int cnt[strsiz]={};
void match(){
    Node* p=root;
    for(int i=0;buf[i];++i){
        if(buf[i]=='z'+1){
            p=root;
            continue;
        }
        int c=buf[i]-'a';
        while(!p->next[c] && p!=root)p=p->fail;
        p=p->next[c];
        if(!p)p=root;
        Node* x=p;
        while(x!=root){
            for(int j=0;j<x->sum.size();++j)
                ++cnt[x->sum[j]];
            x=x->fail;
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)read(i);
    root=newNode();
    for(int i=0;i<n;++i)build(i,begin[i]);
    pre();
    match();
    for(int i=0;i<n;++i)printf("%d\n",cnt[i]);
    return 0;
}

