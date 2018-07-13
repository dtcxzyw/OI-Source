#include <cstdio>
#include <cstring>
int iw[101],w[2001],c[2001],cnt=0;
const int size=40000;
int dp1[size],dp2[size];
void CAS(int& a,int b){
    if(a>b)a=b;
}
int main(){
    int n,t,mw=0,end;
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;++i){
    	scanf("%d",&iw[i]);
		if(iw[i]>mw)mw=iw[i];
	}
	end=t+mw*mw;
    int ci,sum=0;
    for(int i=1;i<=n;++i){
        scanf("%d",&ci);
        sum+=ci*iw[i];
        for(int j=1;j<=ci;j<<=1){
            ++cnt;
            w[cnt]=iw[i]*j;
            c[cnt]=j;
            ci-=j;
        }
        if(ci){
            ++cnt;
            w[cnt]=iw[i]*ci;
            c[cnt]=ci;
        }
    }
    
    if(sum<t){
        puts("-1");
        return 0;
    }
    
    memset(dp1,0x3f,sizeof(dp1));
    memset(dp2,0x3f,sizeof(dp2));
    dp1[0]=0;
    
    for(int i=1;i<=cnt;++i){
        for(int j=end;j>=w[i];--j)
            CAS(dp1[j],dp1[j-w[i]]+c[i]);
    }
    
    dp2[0]=0;
    for(int i=1;i<=n;++i){
        for(int j=iw[i];j<=end;++j)
            CAS(dp2[j],dp2[j-iw[i]]+1);
    }
    
    int ans=0x3f3f3f3f;
    for(int i=t;i<=end;++i){
        int res=dp1[i]+dp2[i-t];
        if(res<ans)
            ans=res;
    }
    
    if(ans==0x3f3f3f3f)puts("-1");
    else printf("%d\n",ans);
    return 0;
}

