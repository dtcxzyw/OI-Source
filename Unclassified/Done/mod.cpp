#include <iostream>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    long long ans=0;
    for(int i=2;i<=(k>>1|1);++i)
        ans+=k%i;
    int begin=(k>>1|1)+1;
    int end=min(k-1,n);
    ans+=(k%begin+k%end)*(end-begin+1)/2;
    if(n>k)ans+=(n-k)*k;
    cout<<ans<<endl;
    return 0;
}

