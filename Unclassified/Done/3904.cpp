#include <cstdio>
#include <algorithm>
struct Num{
private:
	int bit[1000],siz;
public:
	Num():siz(1){
		bit[1]=0;
	}
	void init(){
		bit[1]=1;
	}
	void update(){
		for(int i=1;i<siz;++i){
			bit[i+1]+=bit[i]/10;
			bit[i]%=10;
		}
		while(bit[siz]>10){
			bit[siz+1]=bit[siz]/10;
			bit[siz]%=10;
			++siz;
		}
	}
	void operator+=(const Num& rhs){
		siz=std::max(siz,rhs.siz);
		for(int i=1;i<=siz;++i)
			bit[i]+=rhs.bit[i];
		update();
	}
	Num operator*=(int rhs){
		for(int i=1;i<=siz;++i)
			bit[i]*=rhs;
		update();
	}
	void print(){
		for(int i=siz;i>=1;--i)
			putchar('0'+bit[i]);
		putchar('\n');
	}
};
Num sum[51][51],a;
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    sum[1][1].init();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(i!=1 || j!=1){
              	a=sum[i-1][j];
              	a*=j;
			    sum[i][j]=sum[i-1][j-1];
			    sum[i][j]+=a;
            }
    sum[n][m].print();
    return 0;
}

