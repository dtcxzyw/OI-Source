#include <cstdio>
int sum[100001]={},n,x,y;
inline void add(){
    while(x<=n){
        sum[x]+=y;
        x+=x&-x;
    }
}
int get(int i){
    int res=0;
    while(i){
        res+=sum[i];
        i-=i&-i;
    }
    return res;
}
int main(){
	int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        x=i,scanf("%d",&y);
        add();
    }
    
    char c[2];
    while(m){
        scanf("%s%d%d",c,&x,&y);
        if(*c=='x')add();
        else printf("%d\n",get(y)-get(x-1));
        --m;
    }
    return 0;
}

