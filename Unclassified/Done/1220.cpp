#include <cstdio>
#include <cstring>
int prev[51],next[51],p[51],w[51],ans=1<<30,n,minv[51][51][5001];
void shut(int x,int t,int cw,int num){
	cw+=w[x]*t;
	if(cw>=ans)return;
	if(cw>=minv[x][num][t])return;
	else minv[x][num][t]=cw;
	if(num){
		int pre=prev[x],nxt=next[x];
		next[pre]=nxt,prev[nxt]=pre;
		if(pre>0 && nxt<=n){
			int d1=p[x]-p[pre],d2=p[nxt]-p[x];
		    if(d1<d2){
		    	shut(pre,t+d1,cw,num-1);
		    	shut(nxt,t+d2,cw,num-1);
		    }
		    else{
		    	shut(nxt,t+d2,cw,num-1);
		    	shut(pre,t+d1,cw,num-1);
		    }
		}
		else if(pre>0)shut(pre,t+p[x]-p[pre],cw,num-1);
		else if(nxt<=n)shut(nxt,t+p[nxt]-p[x],cw,num-1);
		next[pre]=prev[nxt]=x;
	}
	else ans=cw;
}
int main(){
	int c;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&p[i],&w[i]),prev[i]=i-1,next[i]=i+1;
	memset(minv,0x3f,sizeof(minv));
	shut(c,0,0,n-1);
	printf("%d\n",ans);
	return 0;
}

