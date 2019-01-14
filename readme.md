![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/dtcxzyw/OI-Source.svg?style=popout-square)
![GitHub All Releases](https://img.shields.io/github/downloads/dtcxzyw/OI-Source/total.svg?style=popout-square)

# Review
## 博弈论
- [x] nim系列游戏
- [x] sg函数
- [x] 对抗搜索 AlphaBeta
- [x] 威佐夫博奕、斐波那契博弈
## 网络流
- [x] 二分图
- [x] 最大流
- [x] 费用流
- [x] 带上下界网络流
- [x] 常见网络流/最小割模型
- [ ] 最小割性质【AHOI2009】最小割
- [ ] 差分建图
- [ ] 消圈定理
## 数据结构
- [x] 树状数组
- [x] 线段树
- [x] 划分树
- [x] 平衡树（fhqtreap/splay）
- [x] LCT
- [x] 并查集
- [x] kd-tree
- [x] 可并堆
- [x] 可持久化数据结构
## 数学
### 数论
- [x] gcd/exgcd
- [x] 费马（线性推逆元）/（EX）欧拉定理
- [x] Miller Rabin
- [x] Pollard Rho
- [x] RSA
- [x] CRT/exCRT
- [x] 线性筛求积性函数值-因子分解
- [x] 狄利克雷卷积，莫比乌斯反演
- [x] 低于线性复杂度筛法
- [x] BSGS/exBSGS
- [x] 原根 映射技巧
### 集合论/群论
- [x] 置换 Polya定理
- [x] 容斥
### 组合数学
- [x] Catalan
- [x] Stirling
- [x] lucas/exLucas
### 多项式
- [x] FFT
- [x] NTT
- [x] FWT
- [x] 实序列DFT
- [x] MTT
- [x] 牛顿迭代法与多项式求逆/取模/ln/exp/三角函数/组合数取模
- [x] FFT封装
### 线性代数
- [x] 高斯消元
- [x] LUP分解/矩阵求逆
- [x] 行列式
- [x] 线性基
- [x] 最小二乘逼近
### 其他
- [x] 泰勒展开
- [x] Simpson积分
- [x] 概率期望
- [x] 生成函数/贝尔数/伯努利数求自然数幂和
- [x] 拉格朗日插值法
- [x] 二项式/斯特林/子集反演
- [x] 常见数学公式
- [x] 线性复杂度插值
## 动态规划
- [x] 背包
- [x] 数位动规
- [ ] 插头dp
- [x] LCIS
### dp优化
- [x] 单调队列
- [x] 斜率优化
- [x] 四边形不等式
- [x] 矩阵快速幂
## 图论
### 树
- [x] LCA
- [x] 树链剖分（重链剖分/长链剖分）
- [x] 树的直径
- [x] 点分治
- [x] 虚树
- [x] purfer序列
- [x] dsu on tree
### 最短路
- [x] SPFA
- [x] Dijskra
- [x] Floyd
- [x] 差分约束
- [x] k短路
### 生成树
- [x] Kruskal/Prim
- [x] Kruskal重构树
- [x] 曼哈顿距离最小生成树
- [x] 生成树性质
- [x] MatrixTree定理、扩展
- [x] 斯坦纳树
### 其他
- [x] 割点，桥
- [x] 强连通分量
- [x] 双连通分量
- [x] 2-SAT
- [x] 仙人掌与圆方树
- [x] 欧拉回路/哈密尔顿回路
- [x] 竞赛图、最小平均值环、平面图性质
## 字符串
- [x] Hash
- [x] Trie/AC自动机
- [x] 后缀树
- [x] 后缀数组
- [x] 后缀仙人掌
- [x] 后缀自动机
- [x] PAM
- [x] KMP
- [x] Manacher
- [x] Huffman
- [x] 表达式解析
- [ ] LL(1) Parser
## 计算几何
- [x] 基础设施-pick定理-切比雪夫距离
- [x] 凸包（[在线凸包](http://dwjshift.logdown.com/posts/285072) /凸包加法/合并/稀疏包分布P614）
- [x] 旋转卡壳
- [x] HPI（WC2012钟诚讲稿-线性判空集）
- [x] 圆的交并/最小圆覆盖/圆的反演
- [x] 平面最近点对
## 最优化问题
- [x] 爬山法
- [x] 模拟退火（分块模拟退火）
- [x] 遗传算法
- [x] A*算法
- [x] 梯度下降
- [x] 01分数规划
## 思想/技巧
- [x] 二分
- [x] 三分
- [x] 补集转化
- [x] 莫队-按照奇偶性排序-树上莫队
- [x] 分块
- [x] MITM
- [x] 倍增
- [x] 随机化
- [x] 按位拆分
- [x] 整体二分
- [x] cdq分治
- [x] 扫描线
- [x] 差分
- [x] 双指针法
- [x] 优先队列维护长序列
- [x] 可删堆
- [x] 二进制分组
## 卡常
- [x] 取模
- [x] 矩阵乘法
- [x] 基于硬件的优化
- [x] 搜索优化
- [x] 位运算技巧 子集枚举
- [x] 数组的清零（对修改部分清零，时间戳）
## 理论
- [x] 主定理
- [x] NP完全性
- [x] 数值编码
-----
# Advance
- [x] 带花树
- [ ] 线段树分治
- [x] HLPP
- [x] min_25筛
- [ ] Berlekamp-Massey[By fjzzq2002](https://www.cnblogs.com/zzqsblog/p/6877339.html)
- [x] ISAP
- [x] IDA*
- [x] DLX
- [ ] 最小树型图
- [x] 单纯形算法
- [x] Johnson
- [ ] 通用筛法
- [ ] 平面性算法
- [ ] 点定位
- [x] 二次剩余、三次剩余、高次剩余
- [ ] 拉格朗日乘数法
- [ ] 常系数齐次线性递推
- [ ] 拉格朗日反演
- [x] 快速莫比乌斯变换
- [ ] 支配树
- [ ] Segment tree beats
- [x] Lindström–Gessel–Viennot lemma
- [ ] 边分治
- [ ] 链分治
- [x] 最小割树
- [x] 势能分析线段树
- [x] 弦图、最大势算法
- [x] Hall定理
- [x] Raney引理
- [x] 快速凸包
- [x] 康托展开
- [ ] ETT(Euler Tour Tree)[By Memphis](http://memphis.is-programmer.com/2015/8/7/linkcutmemphis.99293.html)
- [ ] Top-Tree[By Memphis](http://memphis.is-programmer.com/2015/8/7/linkcutmemphis.99293.html)
- [x] Stoer-Wagner算法
- [x] LCT维护子树信息和边权信息
- [x] 共价大爷游长沙技巧
- [ ] FFT字符串通配[By yyb](https://www.cnblogs.com/cjyyb/p/10132855.html)
- [ ] fractional cascading
- [x] boruvka算法-CF888G
- [x] 动态DP
- [x] ExKMP(Z Algorithm)
- [ ] 二维FFT
- [ ] 欧几里得距离MST[By zball](https://www.cnblogs.com/tmzbot/p/6203547.html)
- [x] 类欧几里得算法
- [ ] 最小方差生成树
- [ ] 牛顿级数差分
- [ ] 拟牛顿法
- [ ] 格林公式[By Trinkle](http://trinkle.blog.uoj.ac/blog/1519)
- [ ] 三元环[By tan90°](https://www.luogu.org/blog/KingSann/fou-chang-yong-di-hei-ke-ji-san-yuan-huan-post)
- [ ] 闭包[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/Closure.html)
- [ ] b-Matching[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/Matching2.html#2)
- [ ] Stable Matching[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/Matching2.html#3)
- [ ] Chinese Postman Problem[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/Circuit.html#4)
- [ ] 启发式分裂[By zsy](https://blog.csdn.net/DSL_HN_2002/article/details/81193576)
- [x] minmax容斥
- [ ] 有标号的DAG计数[By yyb](https://www.cnblogs.com/cjyyb/p/10134575.html)
- [ ] CZT[By myy 再探快速傅里叶变换](http://www.doc88.com/p-4912876232995.html)
- [ ] 优化形式幂级数计算的牛顿法的常数[By negiizhao](http://negiizhao.blog.uoj.ac/blog/4671)
- [ ] 回滚莫队
- [ ] 原根对1求离散对数[By Dance Of Faith](https://www.cnblogs.com/Dance-Of-Faith/p/9905786.html)
- [ ] 集合选数最值一类问题[By tkandi](https://www.cnblogs.com/tkandi/p/9375509.html)
- [ ] 区间加多项式问题[By riteme](https://riteme.github.io/blog/2018-1-28/interval-polynomial.html)
- [ ] 扩展Dijkstra IOI2011 crocodile BZOJ 2622 [2012国家集训队测试]深入虎穴
- [x] 子序列自动机
- [ ] 行列式的几何意义
- [ ] Dilworth定理
- [ ] 杨氏矩阵
- [ ] 一个用SAM维护多个串的根号特技[By Mangoyang](https://www.cnblogs.com/mangoyang/p/10155185.html)
- [ ] IDDFS SPFA判负环[By 姜碧野](https://wenku.baidu.com/view/f22d0d36ee06eff9aef807e9.html)
- [ ] 单位根反演 [By czy](https://czyhe.me/algorithm/unit-root-inv/unit-root-inv/)
- [ ] 线段树合并[By 黄嘉泰](https://wenku.baidu.com/view/88f4e134e518964bcf847c95.html)
- [ ] 线性代数高级算法
# Research
- [ ] 三维凸包与Delaunay剖分的关系[By 刘汝佳](https://wenku.baidu.com/view/e2e2d86f58fafab069dc02f8.html)
- [ ] 利用powerful number求积性函数前缀和[By fjzzq2002](https://www.cnblogs.com/zzqsblog/p/9904271.html)
- [ ] 近似算法
- [ ] ECC+ECM
- [ ] 笛卡尔树 O(n)-O(1) RMQ
- [ ] ID3
- [ ] 卡SPFA
- [ ] 超大斐波那契数取模[By ACdreamer](https://blog.csdn.net/ACdreamers/article/details/25616461)
- [ ] 卡Hash [By dacin21](https://codeforces.com/blog/entry/60442)
- [ ] 卡并查集
- [ ] 最大流算法效率比较
- [ ] 平衡树效率比较
- [ ] NTR算法 [By raffica](https://www.zhihu.com/question/268382638)
- [ ] DC3
- [ ] SA-IS算法
- [ ] Chan's algorithm
- [ ] DoubleArrayTrie
- [ ] 用动态圆方树实现动态仙人掌[By Isrothy](http://isrothy.blog.uoj.ac/blog/3631)
- [ ] 摊还分析
- [ ] 拟阵
- [ ] A Randomized Linear-Time Algorithm to Find Minimum Spanning Trees
- [ ] Micali-Vazirani Algorithm
- [ ] Maximum Matchings via Glauber Dynamics
- [ ] Dial's Algorithm
- [ ] Gabow's Algorithm
- [ ] Nardelli-Proietti-Widmayer Algorithm
- [ ] Karger's Algorithm
- [ ] 最优化方法[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/Optimization.html)
- [ ] 迭代求解线性方程组
- [ ] 求根、不动点与特征点的关系[演算法筆記](http://www.csie.ntnu.edu.tw/~u91029/RootFinding.html#5)
- [ ] Karmarkar's algorithm
- [ ] Mehrotra predictor-corrector method
- [ ] 维护双向加字符的字符串[By 傅笙芳](https://zhuanlan.zhihu.com/p/51880239)
- [ ] 排序网络
- [ ] 超现实数 方展鹏-《浅谈如何解决不平等博弈问题》
- [ ] Schreier-Sims 算法
# Other
- [ ] 使用Vim
- [ ] 学习十指打字(目标：250cpm)
- [ ] 整理引用的Bib与协议问题
