#include <iostream>
#include <algorithm>

long double mat[101][101]={};

int main(){
    int n;
    std::cin>>n;
    mat[n][n]=n;
    for(int i=0;i<n;++i){
        mat[n][i]=mat[i][n]=-1,mat[i][i]=3;
        --mat[i][(i+1)%n];
        --mat[i][(i-1+n)%n];
    }
    
    for(int i=0;i<n;++i){
        for(int j=i;j<=n;++j)
            if(mat[j][i]!=0){
                if(i!=j)
                    for(int k=0;k<=n;++k)
                        std::swap(mat[i][k],mat[j][k]);
                break;
            }
            
        for(int j=i+1;j<=n;++j){
            double t=mat[j][i]/mat[i][i];
            for(int k=i;k<=n;++k)
                mat[j][k]-=mat[i][k]*t;
        }
    }
    
    long double ans=1;
    for(int i=0;i<n;++i)
        ans*=mat[i][i];
    if(ans<0.0)ans=-ans;
    std::cout.precision(0);
    std::cout<<std::fixed<<ans<<std::endl;
    return 0;
}

