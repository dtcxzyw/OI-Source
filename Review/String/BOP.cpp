#include <cstdio>
#include <stack>
std::stack<int> num;
std::stack<char> op;
char buf[1024];
int pri[128];
bool fold() {
    if(num.size() < 2 || op.size() < 1)
        return false;
    int b = num.top();
    num.pop();
    int a = num.top();
    num.pop();
    char oper = op.top();
    op.pop();
    switch(oper) {
        case '+':
            num.push(a + b);
            break;
        case '-':
            num.push(a - b);
            break;
        case '*':
            num.push(a * b);
            break;
        case '/':
            if(b) {
                num.push(a / b);
            } else
                return false;
            break;
    }
    return true;
}
template <typename T>
void clear(T& ct) {
    T empty;
    std::swap(ct, empty);
}
int main() {
    pri['+'] = pri['-'] = 1;
    pri['*'] = pri['/'] = 2;
    while(scanf("%s", buf) != EOF) {
        clear(num);
        clear(op);
        int i;
        for(i = 0; buf[i]; ++i) {
            char c = buf[i];
            if('0' <= c && c <= '9') {
                int number = 0;
                do {
                    number = number * 10 + c - '0';
                    c = buf[++i];
                } while('0' <= c && c <= '9');
                --i;
                num.push(number);
            } else if(c == '(')
                op.push('(');
            else if(c == ')') {
                bool flag = true;
                while(op.size() && op.top() != '(') {
                    if(!fold()) {
                        flag = false;
                        break;
                    }
                }
                if(flag && op.size())
                    op.pop();
                else
                    break;
            } else if(pri[c]) {
                bool flag = true;
                while(op.size() &&
                      pri[op.top()] >= pri[c]) {
                    if(!fold()) {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                    op.push(c);
                else
                    break;
            } else
                break;
        }
        bool flag = true;
        while(op.size()) {
            if(!fold()) {
                flag = false;
                break;
            }
        }
        if(flag && !buf[i] && num.size() == 1)
            printf("%s=%d\n", buf, num.top());
        else
            puts("Error");
    }
    return 0;
}
