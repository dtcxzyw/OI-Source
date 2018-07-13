#include <cstdio>
#include <algorithm>
int A[1010],B[1010],S1[1010],S2[1010],Op[2010],n;
int in=0,s1=0,s2=0,out=0,opc=0;
bool DFS(){
	++opc;
	if(out==n)return true;
	if(in<n && (s1==0||S1[s1-1]>=A[in])){
		Op[opc]='a';
		S1[s1]=A[in];
		++in,++s1;
		if(DFS())return true;
		--in,--s1;
	}
	
	if(s1 && S1[s1-1]==B[out]){
		Op[opc]='b';
		int old=S1[s1-1];
		--s1,++out;
		if(DFS())return true;
		++s1,--out;
		S1[s1-1]=old;
	}
	
	if(in<n && (s2==0||S2[s2-1]>=A[in])){
		Op[opc]='c';
		S2[s2]=A[in];
		++in,++s2;
		if(DFS())return true;
		--in,--s2;
	}
	
	if(s2 && S2[s2-1]==B[out]){
		Op[opc]='d';
		int old=S2[s2-1];
		--s2,++out;
		if(DFS())return true;
		++s2,--out;
		S2[s2-1]=old;
	}
	--opc;
	return false;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&A[i]);
		B[i]=A[i];
	}
	std::sort(B,B+n);
	if(DFS()){
		for(int i=1;i<=n*2;++i){
			putchar(Op[i]);
			putchar(' ');
		}
	}
	else puts("0");
	return 0;
}

