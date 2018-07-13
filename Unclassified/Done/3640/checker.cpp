#include <cstdio>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>
const char* name[6]={
	"FloydWarshall",
	"OptimizedBellmanFord",
	"ModifiedDijkstra",
	"Gamble1",
	"Gamble2",
	"RecursiveBacktracking"
};
struct Task{
	int s,t,a,b;
} tasks[9]={
	{0,0,0,0},
	{3,107,2,0},
	{7,2222,0,1},
	{8,105,1,0},
	{17,157,0,2},
	{10,1016,2,1},
	{19,143,1,2},
	{11,3004,3,5},
	{25,3004,5,4}
};
std::string to_string(int x){
	std::stringstream ss;
	ss<<x;
	return ss.str();
}
int count(int t){
	std::string path="data/"+to_string(t)+".txt";
	freopen(path.c_str(),"r",stdin);
	int tmp,cnt=0;;
	while(scanf("%d",&tmp)!=EOF)++cnt;
	return cnt;
}
int run(int id,int t){
	std::string task="D:/dtcxzyw/3640/data/"+to_string(t)+".txt";
	std::string path="D:/dtcxzyw/3640/bin/"+std::string(name[id])+".exe";
	std::string cmd=path+" <"+task+" >tmp.txt";
	int time=system(cmd.c_str());
	printf("%s return %d\n",name[id],time);
	return time;
}
double calcScore(int S,int T,int F){
	if(F==0)return 0;
	return S*std::min(1.0,1.0*T/F);
}
const int TLE=1000000;
double test(int t){
	Task task=tasks[t];
	printf("test %d Task S=%d T=%d A=%s B=%s\n",t,task.s,task.t,name[task.a],name[task.b]);
	int cnt=count(t);
	printf("input size:%d\n",cnt);
	double score=calcScore(task.s,task.t,cnt);
	if(cnt){
		if((run(task.a,t)>TLE)||(run(task.b,t)<=TLE))
			score=0.0;
	}
	printf("point %d:%.2lf\n",t,score);
	puts("-------------------------------");
	return score;
}
int main(){
	double score=0.0;
	for(int i=1;i<=8;++i)
		score+=test(i);
	printf("Score:%.2lf\n",score);
	return 0;
}

