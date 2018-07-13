#include <cstdio>
#include <set>
#include <cmath>
#include <iterator>
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
struct Point{
	int x,y;
	Point(int a,int b):x(a),y(b){}
	Point operator-(Point rhs) const{
		return Point(x-rhs.x,y-rhs.y);
	}
	int cross(Point rhs) const{
		return x*rhs.y-rhs.x*y;
	}
	bool operator<(Point rhs) const{
		return x*(rhs.y+1)<rhs.x*(y+1);
	}
	bool operator<=(Point rhs) const{
		return x*rhs.y<=rhs.x*y;
	}
	double dis(Point rhs) const{
		int dx=x-rhs.x,dy=y-rhs.y;
		return sqrt(dx*dx+dy*dy);
	}
};
double len;
std::set<Point> S;
typedef std::set<Point>::iterator Iter;
Iter next(Iter it){
	return ++it;
}
Iter prev(Iter it){
	return --it;
}
void push(Point p){
	/*
	printf("insert %d %d\n",p.x,p.y);
	puts("begin");
	for(Iter it=S.begin();it!=S.end();++it)
		printf("%d %d\n",it->x,it->y);
	*/
	Iter r=S.lower_bound(p);
	Iter l=prev(r);
	//printf("L %d %d R %d %d\n",l->x,l->y,r->x,r->y);
	Point ref(0,-1);
	int a=(*l-ref).cross(*r-ref);
	int b=(*l-p).cross(*r-p);
	if(1LL*a*b<0){
		while(true){
			Iter L=prev(l),nl=r;
			if(L!=S.end() && p-*L<=*l-*L){
				len-=(*l).dis(*L)+(*l).dis(*nl);
				len+=(*L).dis(*nl);
				nl=l;
				l=L;
			}
			else break;
		}
		while(true){
			Iter R=next(r),nr=l;
			if(R!=S.end() && *r-*R<=p-*R){
				len-=(*r).dis(*R)+(*r).dis(*nr);
				len+=(*R).dis(*nr);
				nr=r;
				r=R;
			}
			else break;
		}
		
		//printf("L %d %d R %d %d\n",l->x,l->y,r->x,r->y);
		len+=p.dis(*l)+p.dis(*r)-l->dis(*r);
		S.erase(next(l),r);
		S.insert(p);
	}
	/*
	puts("end");
	for(Iter it=S.begin();it!=S.end();++it)
		printf("%d %d\n",it->x,it->y);
	printf("C=%.2lf\n",len);
	*/
}
int P[101000][2],Q[201000],top=0;
double st[201000];
bool flag[101000]={};
int main(){
	int n=read();
	int x=read();
	int y=read();
	int m=read();
	for(int i=1;i<=m;++i){
		P[i][0]=read();
		P[i][1]=read();
	}
	int q=read();
	for(int i=1;i<=q;++i){
		if(read()==1){
			int x=read();
			Q[i]=x;
			flag[x]=true;
		}
		else Q[i]=0;
	}
	Point A(0,0),B(n,0),C(x,y);
	S.insert(A); 
	S.insert(B);
	S.insert(C);
	len=B.dis(C)+C.dis(A);
	for(int i=1;i<=m;++i)
		if(!flag[i])
			push(Point(P[i][0],P[i][1]));
	for(int i=q;i>=1;--i){
		if(Q[i])push(Point(P[Q[i]][0],P[Q[i]][1]));
		else st[++top]=len;
	}
	for(int i=top;i>=1;--i)
		printf("%.2lf\n",st[i]);
	return 0;
}

