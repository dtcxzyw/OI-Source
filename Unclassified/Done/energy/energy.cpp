#include <iostream>
using namespace std;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			ans+=gcd(i,j);
	cout<<ans*2-m*n<<endl;
	return 0;
}

