#include <cstdio>
#include <cmath>
typedef long double FT;
const FT eps=1e-10;
double a;
FT calc(FT x){
    return pow(x,a/x-x);
}
FT simpson(FT l,FT r,FT fl,FT fm,FT fr){
    return (fl+4.0*fm+fr)*(r-l)/6.0;
}
FT simpsonSA(FT l,FT m,FT r,FT base,FT fl,FT fm,FT fr){
    FT lm=(l+m)*0.5,rm=(m+r)*0.5;
    FT flm=calc(lm),frm=calc(rm);
    FT sl=simpson(l,m,fl,flm,fm),sr=simpson(m,r,fm,frm,fr);
    if(fabs(sl+sr-base)<=eps)return base;
    return simpsonSA(l,lm,m,sl,fl,flm,fm)+simpsonSA(m,rm,r,sr,fm,frm,fr);
}
int main(){
    scanf("%lf",&a);
    if(a<0.0)puts("orz");
    else{
    	FT res=0.0,step=fmax(1.0,sqrt(a));
	    FT l=eps,r=step;
	    while(true){
		    FT m=(l+r)*0.5;
		    FT fl=calc(l),fm=calc(m),fr=calc(r);
		    FT sum=simpsonSA(l,m,r,simpson(l,r,fl,fm,fr),fl,fm,fr);
			if(sum>=eps)res+=sum;
			else break;
			l+=step,r+=step;
		}
	    printf("%.5lf\n",static_cast<double>(res));
	}
    return 0;
}

