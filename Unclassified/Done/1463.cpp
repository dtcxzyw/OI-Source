#include <cstdio>
#include <cstring>
const int p[12]={2,3,5,7,11,13,17,19,23,29,31,37};
int n,cnt[5001];
void DFS(int c,int x,int fac,int mp){
    if(cnt[fac]>x)cnt[fac]=x;
    if(c==12)return;
    for(int i=1;i<=mp;++i){
        if(1LL*x*p[c]<n)x*=p[c];
        else break;
        DFS(c+1,x,fac*(i+1),i);
    }
}
int main(){
    scanf("%d",&n);
    memset(cnt,0x7f,sizeof(cnt));
    DFS(0,1,1,30);
    int ans=0,minv=0x7f7f7f7f;
    for(int i=5000;i>=1;--i)
        if(cnt[i]<=n && cnt[i]<minv){
            minv=cnt[i];
            if(cnt[i]>ans)ans=cnt[i];
        }
    printf("%d\n",ans);
    return 0;
}

