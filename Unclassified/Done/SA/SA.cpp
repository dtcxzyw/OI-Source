#include <cstdio>
#include <cstring>
#include <algorithm>
constexpr int size=1000001;
char buf[size];
int buc[size],SA[size],xa[size],ya[size];
int main(){
	gets(buf);
	int *x=xa,*y=ya,m=128;
	int len=strlen(buf),i,k;
	for(i=0;i<m;++i)buc[i]=0;
	for(i=0;i<len;++i)++buc[x[i]=buf[i]];
	for(i=1;i<m;++i)buc[i]+=buc[i-1];
	for(i=len-1;i>=0;--i)SA[--buc[x[i]]]=i;
	int p;
	for(k=1;k<=len;k<<=1){
		p=0;
		for(i=len-1;i>=len-k;--i)y[p++]=i;
		for(i=0;i<len;++i)
			if(SA[i]>=k)
				y[p++]=SA[i]-k;
		for(i=0;i<m;++i)buc[i]=0;
		for(i=0;i<len;++i)++buc[x[y[i]]];
		for(i=1;i<m;++i)buc[i]+=buc[i-1];
		for(i=len-1;i>=0;--i)SA[--buc[x[y[i]]]]=y[i];
		std::swap(x,y);
		p=1,x[SA[0]]=0;
		for(i=1;i<len;++i){
			if(y[SA[i-1]]==y[SA[i]] && y[SA[i-1]+k]==y[SA[i]+k])
				x[SA[i]]=p-1;
			else x[SA[i]]=p++;
		}
		if(p>=len)break;
		m=p;
	}
	for(i=0;i<len;++i)
		printf("%d ",SA[i]+1);
	return 0;
}

