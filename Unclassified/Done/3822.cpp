#include <cstdio>
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
const int size=30*1000010;
const char off=1,on=2,mix=3;
char st[size<<2],col[size<<2];
int pid[size]={};
int siz;
inline void update(int id){
    st[id]=st[id<<1]|st[id<<1|1];
}
inline void color(int id,char mark){
    st[id]=col[id]=mark;
}
void push(int id){
    if(col[id]){
        color(id<<1,col[id]);
        color(id<<1|1,col[id]);
        col[id]=0;
    }
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int nl,nr;
char x;
void modify(int l,int r,int id){
    if(nl<=l && r<=nr)color(id,x);
    else{
        push(id);
        int m=(l+r)>>1;
        if(nl<=m)modify(ls);
        if(m<nr)modify(rs);
        update(id);
    }
}
int k;
char query(int l,int r,int id){
    if(st[id]!=mix)return st[id];
    else{
        push(id);
        int m=(l+r)>>1;
        if(k<=m)return query(ls);
        return query(rs);
    }
}
inline void pushUp(int id){
	while(id>>=1)update(id);
}
void pushDown(int id){
	if(id!=1)pushDown(id>>1);
	push(id);
}
bool addBit(int l,int r,int id,int pos){
    if(st[id]==on){
        nl=pos,nr=r,x=off;
        pushDown(id>>1);
		modify(l,r,id);
		pushUp(id);
        return true;
    }
    else if(st[id]==off){
    	pushDown(pid[pos]>>1);
        st[pid[pos]]=on;
        pushUp(pid[pos]);
        return false;
    }
    else{
    	push(id);
        int m=(l+r)>>1;
        if(pos<=m){
            if(addBit(ls,pos))return addBit(rs,m+1);
            return false;
        }
        return addBit(rs,pos);
    }
}
void add(int a,int b){
    for(int i=0;i<=30;++i)
        if(a&(1<<i))
            addBit(1,siz,1,b+i);
}
bool subBit(int l,int r,int id,int pos){
    if(st[id]==off){
        nl=pos,nr=r,x=on;
        pushDown(id>>1);
        modify(l,r,id);
        pushUp(id);
        return true;	
    }
    else if(st[id]==on){
    	pushDown(pid[pos]>>1);
		st[pid[pos]]=off;
        pushUp(pid[pos]);
        return false;
    }
    else{
    	push(id);
        int m=(l+r)>>1;
        if(pos<=m){
            if(subBit(ls,pos))return subBit(rs,m+1);
            return false;
        }
        return subBit(rs,pos);
    }
}
void sub(int a,int b){
    for(int i=0;i<=30;++i)
        if(a&(1<<i))
            subBit(1,siz,1,b+i);
}
void build(int l,int r,int id){
    if(l!=r){
        int m=(l+r)>>1;
        build(ls);
        build(rs);
    }
    else pid[l]=id;
    st[id]=off,col[id]=0;
}
int main(){
    int n=read();
    siz=(n+2)*30;
    if(siz<200)siz=200;
    build(1,siz,1);
    int t1=read();
    int t2=read();
    int t3=read();
    for(int i=0;i<n;++i){
        if(read()==1){
            int a=read();
            int b=read()+1;
            if(a>0)add(a,b);
            else if(a<0)sub(-a,b);
        }
        else{
            k=read()+1;
            puts(query(1,siz,1)==on?"1":"0");
        }
        /*
        int res=0;
        for(int i=1;i<=30;++i){
            k=i;
            if(query(1,siz,1)==on)res|=1<<(i-1);
        }
        printf("%d\n",res);
        */
    }
    return 0;
}

