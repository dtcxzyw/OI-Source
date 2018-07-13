#include <cstdio>
char buf[40][40];
int p[40],bit[40];
double w[300][5]={};
int getBit(int i,int j){
    return i/bit[j]%3;
}
int setBit(int i,int j,int b){
    return i+bit[j]*(b-2);
}
double maxv(double a,double b){
    return a>b?a:b;
}
int n,m,k;
bool flag[40][40][300][6]={};
double val[40][40][300][6];
const int d[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
double DFS(int x,int y,int s,int h){
    if(flag[x][y][s][h])return val[x][y][s][h];
    flag[x][y][s][h]=true;
    double& res=val[x][y][s][h];
    if(h<=0)res=0.0;
    else if(buf[x][y]=='@')res=1.0;
    else{
        for(int i=0;i<4;++i){
            int cx=x+d[i][0],cy=y+d[i][1];
            if(1<=cx && cx<=n && 1<=cy && cy<=m && buf[cx][cy]!='#'){
                int c=buf[cx][cy],t=c-'A';
                int flag=((0<=t && t<k)?getBit(s,t):0);
                switch(flag){
                    case 0:res=maxv(res,DFS(cx,cy,s,h));break;
                    case 1:res=maxv(res,DFS(cx,cy,s,h-1));break;
                    case 2:res=maxv(res,DFS(cx,cy,setBit(s,t,0),h)*(1.0-w[s][t])+DFS(cx,cy,setBit(s,t,1),h-1)*w[s][t]);break;
                }
            }
        }
    }
    return res;
}
int main(){
    int h;
    scanf("%d%d%d%d",&n,&m,&k,&h);
    int sx,sy;
    for(int i=1;i<=n;++i){
        scanf("%s",buf[i]+1);
        for(int j=1;j<=m;++j)
            if(buf[i][j]=='$')
                sx=i,sy=j;
    }
    int end=1<<k;
    for(int i=0;i<end;++i)
        scanf("%d",&p[i]);
    bit[0]=1;
    for(int i=1;i<=k;++i)bit[i]=bit[i-1]*3;
    for(int s=0;s<bit[k];++s){
        int sum=0;
        for(int i=0;i<end;++i){
            bool flag=true;
            for(int j=0;j<k;++j){
                int x=getBit(s,j);
                if(x!=2 && x!=((i>>j)&1)){
                    flag=false;
                    break;
                }
            }
            if(flag){
                sum+=p[i];
                for(int j=0;j<k;++j){
                    int x=getBit(s,j);
                    if(x>=1 && ((i>>j)&1))w[s][j]+=p[i];
                }
            }
        }
        for(int i=0;i<k;++i)w[s][i]/=sum;
    }
    printf("%.3lf\n",DFS(sx,sy,bit[k]-1,h));
    return 0;
}

