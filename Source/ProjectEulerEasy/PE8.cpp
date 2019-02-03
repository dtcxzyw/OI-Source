#include <cstdio>
const char* S =
    "7316717653133062491922511967442657474235534919493"
    "4969835203127745063262395783180169848018694788518"
    "4385861560789112949495459501737958331952853208805"
    "5111254069874715852386305071569329096329522744304"
    "3557668966489504452445231617318564030987111217223"
    "8311362229893423380308135336276614282806444486645"
    "2387493035890729629049156044077239071381051585930"
    "7960866701724271218839987979087922749219016997208"
    "8809377665727333001053367881220235421809751254540"
    "5947522435258490771167055601360483958644670632441"
    "5722155397536978179778461740649551492908625693219"
    "7846862248283972241375657056057490261407972968652"
    "4145351004748216637048440319989000889524345065854"
    "1227588666881164271714799244429282308634656748139"
    "1912316282458617866458359124566529476545682848912"
    "8831426076900422421902267105562632111110937054421"
    "7506941658960408071984038509624554443629812309878"
    "7992724428490918884580156166097919133875499200524"
    "0636899125607176060588611646710940507754100225698"
    "3155200055935729725716362695618826704282524836008"
    "23257530420752963450";
int main() {
    int n;
    scanf("%d", &n);
    long long res = 0;
    for(int i = 0; i < 1000; ++i) {
        if(i + n > 1000)
            break;
        long long mul = 1;
        for(int j = 0; j < n; ++j)
            mul *= S[i + j] - '0';
        if(mul > res)
            res = mul;
    }
    printf("%lld\n", res);
    return 0;
}
