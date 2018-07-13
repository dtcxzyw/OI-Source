#include <cstdio>
#include <cstring>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
unsigned int SA, SB, SC;
unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
int p,A,B,m;
void get(int i,int& a,int& b){
	if(i<=p){
		a=read()%m;
		b=read();
	}
	else{
		a=(rng61()%A+1)%m;
        b=rng61()%B+1;
	}
}
const int size=205;
int k,dpSiz;
inline long long dis(int a,int b){
	return a<=b?b-a:m-(a-b);
}
inline int mod(int a){
	return a>=m?a-m:a;
}
struct Dp{
	long long val[size];
	void reset(){
		memset(val,0x3f,dpSiz);
	}
	long long& operator[](int id){
		return val[id];
	}
};
int a[2049];
long long S[2049][size],Si[2049][size];
Dp DFS(int u,int d){
	Dp dp;
	if(d==k){
		for(int i=0;i<m;++i)
			dp[i]=Si[u][i];
	}
	else{
		Dp l=DFS(u<<1,d+1);
		Dp r=DFS(u<<1|1,d+1);
		dp.reset();
		for(int i=0;i<m;++i)
			for(int j=0;j<m;++j)
				dp[i]=std::min(dp[i],l[j]+r[j]+Si[u][mod(a[u]+dis(mod(a[u]+j),i))]);
	}
	return dp;
}
long long foo(){
	memset(S,0,sizeof(S));
	int n;
    scanf("%d%d%d%d%u%u%u%d%d", &n, &k, &m, &p, &SA, &SB, &SC, &A, &B);
    dpSiz=sizeof(long long)*m;
	int siz=2<<k;
	for(int i=1;i<siz;++i){
		int b;
		if(i<=n)get(i,a[i],b);
		else a[i]=b=0;
		S[i][a[i]]=b;
	}
	int shift=k+1;
	for(int i=siz;i<=n;++i){
    	int a,b;
		get(i,a,b);
		int x=i;
		while(x>=siz)x>>=shift;
    	S[x][a]+=b;
	}
	for(int i=1;i<siz;++i)
		for(int j=0;j<m;++j){
			long long res=0;
			for(int c=0;c<m;++c)
				res+=S[i][c]*dis(c,j);
			Si[i][j]=res;
		}
	return DFS(1,0)[0];
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)printf("%lld\n",foo());
	return 0;
}

