#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=(c=='-');
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int SS=1005,ST=1006,size=1010;
int fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void link(int a,int b){
	a=find(a),b=find(b);
	if(a!=b)fa[a]=b;
}
struct Point{
	long long x,y,z;
	void input(){
		x=read();
		y=read();
		z=read();
	}
	long long dis2(const Point& rhs) const{
		long long dx=x-rhs.x,dy=y-rhs.y,dz=z-rhs.z;
		return dx*dx+dy*dy+dz*dz;
	}
} P[size];
bool foo(){
	int n=read();
	int h=read();
	int r=read();
	long long r2=r;
	r2*=r;
	r2*=4;
	for(int i=1;i<=n;++i)
		P[i].input();
	fa[SS]=SS,fa[ST]=ST;
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j)
			if(P[i].dis2(P[j])<=r2)
				link(i,j);
		if(P[i].z<=r)link(i,SS);
		if(P[i].z+r>=h)link(i,ST);
	}
	return find(SS)==find(ST);
}
int main(){
	freopen("cheese.in","r",stdin);
	freopen("cheese.out","w",stdout);
	int t=read();
	for(int i=0;i<t;++i)puts(foo()?"Yes":"No");
	return 0;
}

