# 完成 Lecture 5 过程中的感想

## Overview
在CS50的所有内容中（到此为止），Data Structure是最复杂的，也是我在上面花费时间最多的一个Lecture。
但认真学完，确实受益匪浅，至少现在已经对各个数据结构有了一个比较完整的认识。

David讲的大课基本以理论为主，当有一个很大的感觉就是，理论和实际操作起来是两回事。对于实践部分，
这一次的shorts可以说是干货满满，介绍了各种数据结构的基本操作方法。具体做Pset的时候，没有先看shorts导致做Inheritance
的时候基本都处于一个云里雾里的状态。不过这样子学，印象也可能会更深刻😂有点塞翁失马的感觉

## Specify on speller

### 在蹒跚学步中完成V0.1
Speller的总体难度相比之前也丝毫不减啊。首先就是这个阅读量真的相当感人。理解总体的含义就花了一个小时（10.24晚上），
现在看起来，理解过后再完成其实也就是按部就班(10.25早上)，但是。。在这个过程中耗费的脑力也一点不少。这个版本写完之后测了一下效率，
贼低。。差不多都要1秒以上。相比起来staff'ssolution就像是外星科技一样。。不过这还是也累了，就先去看shorts了。

### 转到Trie: 一个很自然的想法
看shorts的过程中逐渐形成了这一个意识：数据结构在空间与时间上是tradeoff的关系。听到tries这种结构的时候，就觉得非常适合拿来做
speller的数据结构，时间复杂度θ(1)的吸引力还是很大的。所以从10.25晚上就开始动工。在动工过程中，真的得好好感谢cs50 duck。
他给了我一个很有用的建议：就是把trie中储存name的部分改成一个bool，is_name。看到这里有一种很大的茅塞顿开的感觉。
接下去思路就非常明确了。还剩一些小的问题，比如应该分配27个地址（留一个给'），还有load模块里要注意是否需要创建新的模块，这些都写在
dictionary.c里面了，就不多说。

## Lastly
这是第一次在Pset之外给自己安排内容，在这个过程中是真的能感受到写代码和不断学习学习的快乐，就像cs50 staff说的，越来越接近数据结构的Holy Grail🏆
> Keep learning💪