#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <limits>

std::string to_string() {
    return "\n";
}

template<typename FirstT, typename... ArgTs>
std::string to_string(FirstT&& first, ArgTs&&... args) {
    std::stringstream ss;
    ss.precision(32);
    ss << std::fixed << first << ' ';
    return ss.str() + to_string(std::forward<ArgTs>(args)...);
}

class Printer final {
private:
    size_t mLine;
    std::unordered_map<std::string, size_t> mCache;
public:
    Printer() : mLine(0) {}
    template<typename... ArgTs>
    size_t print(ArgTs&&... args) {
        auto code = to_string(std::forward<ArgTs>(args)...);
        auto cache = mCache.find(code);
        if (cache == mCache.cend() || code.front()=='I' || code.front()=='O') {
            std::cout << code;
            mCache.insert({ code,++mLine });
            return mLine;
        }
        return cache->second;
    }
};

class Value {
private:
    static constexpr size_t max = 10000;
    mutable size_t mLine = max;
public:
    size_t get(Printer& out) const {
        return mLine = (mLine != max ? mLine : output(out));
    }
    virtual size_t output(Printer& out) const = 0;
    virtual ~Value() = default;
};

class Constant final {
private:
    bool mIsInt, mIsString;
    int64_t mInt;
    double mFloat;
    std::string mString;
public:
    template<typename T>
    Constant(T v) :mIsInt(std::is_integral<T>::value), mIsString(false) {
        if (mIsInt)mInt = v;
        else mFloat = v;
    }

    Constant(const char* str) :mString(str), mIsString(true), mIsInt(false) {}

    void output(std::ostream& out) const {
        if (mIsInt) out << mInt;
        else if (mIsString) out << mString;
        else out << mFloat;
    }
    double get() const {
        if (mIsInt)return mInt;
        else if (mIsString) {
            std::stringstream ss;
            ss << mString;
            double r;
            ss >> r;
            return r;
        }
        return mFloat;
    }
    Constant operator+(Constant rhs) const {
        if (mIsInt && rhs.mIsInt)
            return mInt + rhs.mInt;
        return get() + rhs.get();
    }
    Constant operator-() const {
        if (mIsInt)return -mInt;
        else if (mIsString) return ((mString.front() != '-') ? ("-" + mString) : (mString.substr(1))).c_str();
        return -mFloat;
    }
};

std::ostream& operator<<(std::ostream& out, Constant c) {
    c.output(out);
    return out;
}


using SharedValue = std::shared_ptr<Value>;

//Base

struct Input final :public Value {
    size_t output(Printer& out) const override {
        return out.print('I');
    }
};

template<size_t size>
using Args = const std::array<SharedValue, size>;

#define Constructor(name,size) \
Args<size> args;\
name(const Args<size>& _args):args(_args){}

#define ConstructorEx(name,ct) \
Args<1> args;\
const ct constant;\
name(const Args<1>& _args,ct _constant):args(_args),constant(_constant){}

#define Get(id) (args[id]->get(out))

struct Add final : public Value {
    Constructor(Add, 2);
    size_t output(Printer& out) const override {
        return out.print('+', Get(0), Get(1));
    }
};

struct AddConstant final : public Value {
    ConstructorEx(AddConstant, Constant);
    size_t output(Printer& out) const override {
        return out.print('C', Get(0), constant);
    }
};

struct Neg final :public Value {
    Constructor(Neg, 1);
    size_t output(Printer& out) const override {
        return out.print('-', Get(0));
    }
};

struct LMove final :public Value {
    ConstructorEx(LMove, uint16_t);
    size_t output(Printer& out) const override {
        return out.print('<', Get(0), constant);
    }
};

struct RMove final :public Value {
    ConstructorEx(RMove, uint16_t);
    size_t output(Printer& out) const override {
        return out.print('>', Get(0), constant);
    }
};

struct SFunc final :public Value {
    Constructor(SFunc, 1);
    size_t output(Printer& out) const override {
        return out.print('S', Get(0));
    }
};

SharedValue input(Printer& out) {
    auto v = std::make_shared<Input>();
    v->get(out);
    return v;
}

void operator<<(Printer& out, SharedValue value) {
    out.print('O', value->get(out));
}

SharedValue operator+(SharedValue a, SharedValue b) {
    if (a)
        return std::make_shared<Add>(Args<2>{ a, b });
    return b;
}

SharedValue operator+(SharedValue a, Constant b) {
    auto p = std::dynamic_pointer_cast<AddConstant>(a);
    if (p) {
        if ((p->constant + b).get() != 0.0)
            return std::make_shared<AddConstant>(p->args, p->constant + b);
        return a;
    }
    return std::make_shared<AddConstant>(Args<1>{ a }, b);
}

SharedValue operator-(SharedValue a, Constant b) {
    return a + -b;
}

SharedValue operator-(SharedValue x) {
    return std::make_shared<Neg>(Args<1>{ x });
}

SharedValue operator-(SharedValue a, SharedValue b) {
    return a + (-b);
}

SharedValue operator<<(SharedValue a, uint16_t b) {
    auto p = std::dynamic_pointer_cast<LMove>(a);
    if (p) return std::make_shared<LMove>(p->args, p->constant + b);
    if (b == 0) return a;
    if (a)
        return std::make_shared<LMove>(Args<1>{ a }, b);
    return a;
}

SharedValue operator>>(SharedValue a, uint16_t b) {
    auto p = std::dynamic_pointer_cast<RMove>(a);
    if (p) return std::make_shared<RMove>(p->args, p->constant + b);
    if (b == 0) return a;
    if (a)
        return std::make_shared<RMove>(Args<1>{ a }, b);
    return a;
}

SharedValue S(SharedValue x) {
    return std::make_shared<SFunc>(Args<1>{ x });
}

#undef Constructor
#undef ConstructorEx
#undef Get

//Func EXT

//2
SharedValue cmpZeroBase(SharedValue x) {
    return S(x << 500);
}

//4
SharedValue cmpZero(SharedValue x) {
    return (cmpZeroBase(x) << 1) - 1;
}

//8
SharedValue operator^(SharedValue bita, SharedValue bitb) {
    auto i = bita + bitb;
    auto sub = cmpZeroBase(i - 1.5) << 1;
    return i - sub;
}

//14
SharedValue abs(SharedValue x) {
    auto p = cmpZeroBase(x + 1e-20) << 102;
    auto y = S((x >> 100) + p);
    return x + ((-y + 0.5) << 103) + p;
    //x>0 p=1<<102 y=1 res=x-1<<102+1<<102=x
    //x=0 p=1<<102 y=1 res=0-1<<102+1<<102
    //x<0 p=0 y=S(x>>100)=0.5+x>>102 res=x-x<<1+0=-x
}

//20
std::pair<SharedValue, SharedValue> minmaxv(SharedValue a, SharedValue b) {
    auto c = (a + b) >> 1;
    auto d = abs(a - b) >> 1;
    return { c - d,c + d };
}

std::vector<SharedValue> toBits(SharedValue a) {
    std::vector<SharedValue> res;
    constexpr int add = 30;
    auto ba = a << add;
    for (int16_t j = 31; j > 0; --j) {
        auto c = S(ba - ((1ULL << (add + j)) - (1ULL << 29)));
        res.emplace_back(c);
        ba = ba - (c << (add + j));
    }
    res.emplace_back(ba >> add);
    return res;
}

//bit==1 ->0
//bit==0 ->x
SharedValue branchBit(SharedValue bit, SharedValue x) {
    auto p = bit << 102;
    auto y = S((x >> 100) + p);
    return  (((y - 0.5) << 103) - p) >> 1;
    //bit==1 p=1<<102 y=1 res=(1<<102-1<<102)>>1=0
    //bit==0 p=0 y=S(x>>100)=0.5+x>>102 res=(x<<1-0)>>1=x
}

//a>0 -> 0
//a<=0 ->-2b
//12
SharedValue branch(SharedValue a, SharedValue b) {
    auto p = cmpZeroBase(a - 0.5) << 102;
    auto y = S((b >> 100) + p);
    return  ((-y + 0.5) << 103) + p;
    //a>0 p=1<<102 y=1 res = (-1<<102+1<<102)>>1=0
    //a<=0 p=0 y=S(b>>100)=0.5+b>>102 res = -b<<1+0=-2b
}

SharedValue mod(SharedValue a, SharedValue b) {
    if (a)
        return a + branch(b - a, b>>1);
    //a>=b res=a-b=a%b
    //a<b res=a+0=a%b
    return a;
}

//Tasks

template<size_t id>
void printTask(Printer&) {}

#define TaskDef(id) template<> void printTask<id>(Printer& out)

TaskDef(1) {
    auto a = input(out), b = input(out);
    auto ans = -(a + b) << 1;
    out << ans;
}

TaskDef(2) {
    auto a = input(out);
    out << S(-((a << 4) + a));
}

TaskDef(3) {
    auto a = input(out);
    out << cmpZero(a);
}

TaskDef(4) {
    auto a = input(out);
    out << abs(a);
}

TaskDef(5) {
    auto sum = input(out);
    for (size_t i = 1; i < 32; ++i)
        sum = (sum << 1) + input(out);
    out << sum;
}

TaskDef(6) {
    auto a = input(out);
    auto ba = toBits(a);
    for (auto&& b : ba)
        out << b;
}

TaskDef(7) {
    auto a = input(out);
    auto ba = toBits(a);
    auto b = input(out);
    auto bb = toBits(b);
    SharedValue ans = ba[0] ^ bb[0];
    for (int i = 31; i > 0; --i) {
        ans = ans << 1;
        ans = ans + (ba[i] ^ bb[i]);
    }
    out << ans;
}

TaskDef(8) {
    auto a = input(out);
    Constant x("-2.06343706889556054672728117262013187145659144988339249983");
    Constant sx("0.112701665379258311482073460021760038916707829470840917341");
    out << ((S((a >> 100) + x) - sx) << 100);
}

TaskDef(9) {
    std::array<SharedValue, 16> array;
    for (auto&& x : array)
        x = input(out);
    for (int i = 0; i < 16; ++i)
        for (int j = i + 1; j < 16; ++j) {
            auto res = minmaxv(array[i], array[j]);
            array[i] = res.first;
            array[j] = res.second;
        }
    for (auto&& x : array)
        out << x;
}

TaskDef(10) {
    auto a = input(out);
    auto ba = toBits(a);
    auto b = input(out);
    b = -b + std::numeric_limits<uint32_t>::max();
    auto bb = toBits(b);
    auto m = input(out);
    SharedValue am;
    for (size_t i = 0; i < 32; ++i)
        am = mod((am << 1) + ba[i], m);
    SharedValue res, add = am;
    for (size_t i = 0; i < 32; ++i) {
        res = mod(res + branchBit(bb[31 - i], add), m);
        add = mod(add << 1, m);
    }
    out << res;
}

#undef TaskDef

//Main

template<size_t id>
void print(size_t i) {
    if (i == id) {
        Printer printer;
        printTask<id>(printer);
    }
    else print<id - 1>(i);
}

template<>
void print<0>(size_t) {}

int main() {
    size_t i;
    std::cin >> i;
    print<10>(i);
    return 0;
}

