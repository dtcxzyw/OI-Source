#include <cstdio>
#include <cstring>
char P[201],buf[30];
int next[201];
const int size=2000;
class String{
private:
    char cache[size];
    int num,b,e;
public:
    String():num(0),b(0),e(0){}
    bool empty() const{
		return b==e;
	}
    char front(){
        if(empty()){
            ++num;
            int v=num,p=0;
            while(v){
            	buf[p++]=v%10+'0';
            	v/=10;
			}
			while(p){
				cache[e]=buf[--p];
				e=(e+1)%size;
			}
        }
        return cache[b];
    }
    void pop(){
        b=(b+1)%size;
    }
} str;
int main(){
    scanf("%s",P);
    const int len=strlen(P);
    int i,j=0;
    next[0]=next[1]=0;
    for(i=1;i<len;++i){
        while(j&&P[i]!=P[j])j=next[j];
        j+=P[i]==P[j];
        next[i+1]=j;
    }
    j=0;
    i=0;
    while(true){
        while(j&&str.front()!=P[j])j=next[j];
        j+=str.front()==P[j];
        if(j==len){
            printf("%d\n",i-j+2);
            return 0;
        }
        str.pop();
        ++i;
    }
    return 0;
}

