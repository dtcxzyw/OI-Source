#include <cstdio>
#include <map>
int lastAns=0;
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return (flag?-res:res)-lastAns;
}
void print(int val){
	lastAns=val;
	printf("%d\n",val);
}
int getRand(){
	static int seed=2143;
	return seed=seed*48271LL%2147483647;
}
const int size=100005;
struct Node{
	int val,beg,end,ls,rs,pri,siz,ssiz;
} T[size*3];
int newNode(int val,int beg,int end){
	static int cnt=0;
	if(beg<end){
		int id=++cnt;
		T[id].val=val;
		T[id].beg=beg;
		T[id].end=end;
		T[id].ls=T[id].rs=0;
		T[id].pri=getRand();
		T[id].siz=T[id].ssiz=end-beg;
		return id;
	}
	return 0;
}
void update(int u){
	T[u].siz=T[T[u].ls].siz+T[T[u].rs].siz+T[u].ssiz;
}
int merge(int x,int y){
	if(x&&y){
		if(T[x].pri<T[y].pri){
			T[x].rs=merge(T[x].rs,y);
			update(x);
			return x;
		}
		else{
			T[y].ls=merge(x,T[y].ls);
			update(y);
			return y;
		}
	}
	return x|y;
}
void split(int u,int w,int id,int& x,int& y,int& z,int& rank){
	if(u){
		if(T[u].val==w && T[u].beg<=id && id<T[u].end){
			rank+=T[T[u].ls].siz+id-T[u].beg+1;
			x=merge(T[u].ls,newNode(w,T[u].beg,id));
			y=merge(newNode(w,id+1,T[u].end),T[u].rs);
			z=newNode(w,id,id+1);
		}
		else{
			if(T[u].val<w || (T[u].val==w && T[u].end<=id)){
				rank+=T[T[u].ls].siz+T[u].ssiz;
				x=u;
				split(T[u].rs,w,id,T[u].rs,y,z,rank);
			}
			else{
				y=u;
				split(T[u].ls,w,id,x,T[u].ls,z,rank);
			}
			update(u);
		}
	}
	else x=y=0;
}
int kth(int u,int w,int id){
	if(u==0)return 0;
	if(T[u].val==w && T[u].beg<=id && id<T[u].end)return T[T[u].ls].siz+id-T[u].beg+1;
	if(T[u].val<w || (T[u].val==w && T[u].end<=id))return T[T[u].ls].siz+T[u].ssiz+kth(T[u].rs,w,id);
	return kth(T[u].ls,w,id);
}
int find(int u,int k){
	if(u==0)return 0;
	int lsiz=T[T[u].ls].siz;
	if(k<=lsiz)return find(T[u].ls,k);
	k-=lsiz;
	if(k<=T[u].ssiz)return T[u].beg+k-1;
	k-=T[u].ssiz;
	return find(T[u].rs,k);
}
typedef std::map<int,int> Map;
typedef Map::iterator IterT;
Map mapInput,mapOutput;
int inputRemap(int x,int y=0){
	IterT it=mapInput.find(x);
	if(it==mapInput.end()){
		if(y)mapInput[y]=x,mapOutput[x]=y;
		return x;	
	}
	int id=it->second;
	if(y){
		mapInput.erase(it);
		mapInput[y]=id;
		mapOutput[id]=y;
	}
	return id;
}
int outputMap(int x){
	IterT it=mapOutput.find(x);
	if(it==mapOutput.end())return x;
	return it->second;
}
Map w;
int getW(int id){
	IterT it=w.find(id);
	if(it==w.end())return 0;
	return it->second;
}
int main(){
	int n=read();
	int m=read();
	int root=newNode(0,1,n+1);
	int minw=0,maxw=0;
	for(int i=0;i<m;++i){
		switch(read()+lastAns){
			case 1:{
				int x=read();
				int y=read();
				int id=inputRemap(x,y);
				print(kth(root,getW(id),id));
				break;
			}
			case 2:{
				int id=inputRemap(read());
				int lt=0,rt=0,p=0,rk=0;
				split(root,getW(id),id,lt,rt,p,rk);
				T[p].val=w[id]=--minw;
				root=merge(merge(p,lt),rt);
				print(rk);
				break;
			}
			case 3:{
				int id=inputRemap(read());
				int lt=0,rt=0,p=0,rk=0;
				split(root,getW(id),id,lt,rt,p,rk);
				T[p].val=w[id]=++maxw;
				root=merge(merge(lt,rt),p);
				print(rk);
				break;
			}
			case 4:{
				int rk=read();
				int id=find(root,rk);
				print(outputMap(id));
				break;
			}
		}
	}	
	return 0;
}

