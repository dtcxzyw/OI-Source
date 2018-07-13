#include <cstdio>
#include <cstring>
#include <algorithm>
const int LUT[10]={0,0,0,0,1,0,0,0,2,0};
long long dp[15][3][3][3][10]={};
void pre(){
	for(int i=0;i<10;++i)dp[1][0][LUT[i]][0][i]=1;
	for(int i=1;i<11;++i)
		for(int j=0;j<3;++j)
			for(int k=0;k<3;++k)
				for(int l=0;l<=j;++l)
					for(int a=0;a<10;++a){
						long long val=dp[i][j][k][l][a];
						for(int b=0;b<10;++b){
							if(k==2 && b==4)continue;
							if(k==1 && b==8)continue;
							int nk=std::max(k,LUT[b]);
							if(a==b){
								int st=std::min(2,l+1);
								dp[i+1][std::max(j,st)][nk][st][b]+=val;
							}
							else{
								dp[i+1][j][nk][0][b]+=val;
							}
						}
					}
}
struct State{
	int j,k,l,m;
	State():j(0),k(0),l(0),m(10){}
	bool insert(int x){
		if(k==2 && x==4)return false;
		if(k==1 && x==8)return false;
		k=std::max(k,LUT[x]);
		if(x==m){
			l=std::min(2,l+1);
			j=std::max(j,l);
		}
		else{
			l=0;
			m=x;
		}
		return true;
	}
};
int B[15];
long long query(long long n){
	int cnt=0;
	while(n){
		B[++cnt]=n%10;
		n/=10;
	}
	if(cnt<11)return 0;
	State cur;
	long long res=0;
	for(int i=11;i>=1;--i){
		int len=i-1;
		for(int j=(i==11);j<B[i];++j){
			State now=cur;
			if(now.insert(j)){
				if(len==0 && now.j==2){
					++res;
					continue;
				}
				for(int k=0;k<3;++k){
					if(now.k==1 && k==2)continue;
					if(now.k==2 && k==1)continue;
					if(now.j==2){
						for(int ml=0;ml<3;++ml)
							for(int l=0;l<=ml;++l)
								for(int x=0;x<10;++x)
									res+=dp[len][ml][k][l][x];
					}
					else{
						for(int x=0;x<10;++x){
							if(now.m==x){
								for(int ml=0;ml<3;++ml)
									for(int l=0;l<=ml;++l)
										if(ml==2 || (l|now.l))
											res+=dp[len][ml][k][l][x];
							}
							else{
								for(int l=0;l<3;++l)
									res+=dp[len][2][k][l][x];
							}
						}
					}
				}
			} 
		}
		if(!cur.insert(B[i]))break;
		if(i==1 && cur.j==2)
			++res;
	}
	return res;	
}
int main(){
	pre();
	long long l,r;
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",query(r)-query(l-1));
	return 0;
}

