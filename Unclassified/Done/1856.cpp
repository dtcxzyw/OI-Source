#include <cstdio>
#include <algorithm>
#include <cstring>
const int size=10010;
struct Line{
    int l,r,h,flag;
    bool operator<(const Line& rhs) const{
        return h==rhs.h?flag<rhs.flag:h<rhs.h;
    }
} lines[size];
struct Seg{
    int cnt,len;
} seg[size<<2];
int map[size];
void update(int l,int r,int id){
    if(seg[id].cnt!=0)seg[id].len=map[r+1]-map[l];
    else if(l==r)seg[id].len=0;
    else seg[id].len=seg[id<<1].len+seg[id<<1|1].len;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int v,int nl,int nr){
    if(l==nl && r==nr) seg[id].cnt+=v;
    else{
        int m=(l+r)>>1;
        if(nr<=m)modify(ls,v,nl,nr);
        else if(nl>m)modify(rs,v,nl,nr);
        else{
            modify(ls,v,nl,m);
            modify(rs,v,m+1,nr);
        }
    }
    update(l,r,id);
}
int ABS(int x){
    return x>0?x:-x;
}
int foo(int n){
	memset(seg,0,sizeof(seg));
	int cnt=1;
    for(int i=0;i<n;++i){
        map[cnt++]=lines[i<<1].l;
		map[cnt++]=lines[i<<1].r;
	}
    std::sort(map+1,map+cnt);
    int siz=std::unique(map+1,map+cnt)-map;
    map[siz]=map[siz-1];
    n<<=1;
    std::sort(lines,lines+n);
    int last=0,ans=0;
    for(int i=0;i<n;++i){
        int l=std::lower_bound(map+1,map+siz,lines[i].l)-map;
        int r=std::lower_bound(map+1,map+siz,lines[i].r)-map;
        modify(1,siz-1,1,lines[i].flag,l,r-1);
        ans+=ABS(seg[1].len-last);
        last=seg[1].len;
    }
    return ans;
}
int rect[5001][4];
int read(){
    int res=0,c;
    bool flag=false;
    do{
        c=getchar();
        flag|=c=='-';
    }while(c<'0' || c>'9');
    while('0'<=c && c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return flag?-res:res;
}
int main(){
    int n=read();
    for(int i=0;i<n;++i)
        for(int j=0;j<4;++j)
            rect[i][j]=read();
    //x bottom->top
    for(int i=0;i<n;++i){
        Line& up=lines[i<<1];
        up.flag=-1,up.l=rect[i][0],up.r=rect[i][2],up.h=rect[i][1];
        Line& down=lines[i<<1|1];
        down.flag=1,down.l=rect[i][0],down.r=rect[i][2],down.h=rect[i][3];
    }
    int res=foo(n);
    //y left->right
    for(int i=0;i<n;++i){
        Line& up=lines[i<<1];
        up.flag=-1,up.l=rect[i][1],up.r=rect[i][3],up.h=rect[i][0];
        Line& down=lines[i<<1|1];
        down.flag=1,down.l=rect[i][1],down.r=rect[i][3],down.h=rect[i][2];
    }
    res+=foo(n);
    printf("%d\n",res);
    return 0;
}

