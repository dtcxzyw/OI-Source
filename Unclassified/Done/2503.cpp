#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
int A[25],pos[25];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int sum=0.0;
    for(int i=0;i<n;++i){
        scanf("%d",&A[i]);
        sum+=A[i];
    }
    double ave=static_cast<double>(sum)/m;
    int ans=1<<30;
    const int end=1<<15;
    int time=0;
    while(time<end){
        int s[6]={};
        for(int j=0;j<n;++j){
            pos[j]=rand()%m;
            s[pos[j]]+=A[j];
        }
        int res=0;
        for(int j=0;j<m;++j)res+=s[j]*s[j];
        double t=10000;
        int cnt=0;
        while(t>1 && cnt<5){
            t*=0.95;
            int p=rand()%n;
            int dst;
            if(t>100)dst=std::min_element(s,s+m)-s;
            else dst=rand()%m;
            if(dst==pos[p])continue;
            int delta=2*(s[dst]-(s[pos[p]]-A[p]))*A[p];
            if(delta<0 || (rand()%10000>exp(-delta/t)*10000)){
                s[pos[p]]-=A[p];
                pos[p]=dst;
                s[pos[p]]+=A[p];
                res+=delta;
            }
            else ++cnt;
        }
        if(res<ans)ans=res,time=0;
        else ++time;
    }
    printf("%.2lf\n",sqrt(static_cast<double>(ans)/m-ave*ave));
    return 0;
}

