#include <cstdio>
#include <algorithm>
using namespace std;
double sum[100001];
int b,e,q[100001],A[100001];
int main(){
    int n,s,t;
    scanf("%d%d%d",&n,&s,&t);
    double l=-10000,r=10000;
    for(int i=1;i<=n;++i)
        scanf("%lld",&A[i]);
    
    sum[0]=0;
    while(r-l>1e-4){
        double mid=(l+r)/2.0;
        bool flag=false;
        b=e=0;
        for(int i=1;i<=n;++i){
            sum[i]=sum[i-1]+A[i]-mid;
            if(i>=s){
                while(b<e && sum[i-s]<sum[q[e-1]])--e;
                q[e++]=i-s;
                if(b<e && q[b]<i-t)++b;
                if(sum[i]>=sum[q[b]]){
                    flag=true;
                    break;
                }
            }
        }
        if(flag)l=mid;
        else r=mid;
    }
    
    printf("%.3lf\n",l);
    return 0;
}

