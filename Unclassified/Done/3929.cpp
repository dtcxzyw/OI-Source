#include <cstdio>
const int maxv=1<<30;
int main(){
	int n;
	while(~scanf("%d",&n)){
		int x,l1,l2,cnt1=0,cnt2=0;
		scanf("%d",&l1);
		l2=l1;
		for(int i=1;i<n;++i){
			scanf("%d",&x);
			if(i&1 && x<l1)l1=maxv,++cnt1;
			else if(~i&1 && x>l1)l1=-maxv,++cnt1;
			else l1=x;
			if(i&1 && x>l2)l2=-maxv,++cnt2;
			else if(~i&1 && x<l2)l2=maxv,++cnt2;
			else l2=x;
		}
		puts((cnt1<cnt2?cnt1:cnt2)<=1?"Yes":"No");
	}
	return 0;
}

