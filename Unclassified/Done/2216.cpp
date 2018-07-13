#include <cstdio>
#include <deque>
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
int A[1001],maxv[1001][1001],minv[1001][1001];
int main(){
	int a,b,n;
	a=read();
	b=read();
	n=read();
	for(int i=1;i<=a;++i){
		std::deque<int> maxq,minq;
		for(int j=1;j<=b;++j){
			A[j]=read();
			while(maxq.size() && A[maxq.back()]<=A[j])maxq.pop_back();
			maxq.push_back(j);
			while(maxq.size() && j-maxq.front()>=n)maxq.pop_front();
			while(minq.size() && A[minq.back()]>=A[j])minq.pop_back();
			minq.push_back(j);
			while(minq.size() && j-minq.front()>=n)minq.pop_front();
			if(j>=n)
				maxv[i][j]=A[maxq.front()],minv[i][j]=A[minq.front()];
		}
	}
	int ans=1<<30;
	for(int i=n;i<=b;++i){
		std::deque<int> maxq,minq;
		for(int j=1;j<=a;++j){
			while(maxq.size() && maxv[maxq.back()][i]<=maxv[j][i])maxq.pop_back();
			maxq.push_back(j);
			while(maxq.size() && j-maxq.front()>=n)maxq.pop_front();
			while(minq.size() && minv[minq.back()][i]>=minv[j][i])minq.pop_back();
			minq.push_back(j);
			while(minq.size() && j-minq.front()>=n)minq.pop_front();
			if(j>=n){
				int maxw=maxv[maxq.front()][i];
				int minw=minv[minq.front()][i];
				ans=std::min(ans,maxw-minw);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

