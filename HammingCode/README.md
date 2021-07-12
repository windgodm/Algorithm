# 汉明码
这是汉明码（hamming code）的实现。

## 需要用到的一些公式

若奇偶校验位的个数为n：

汉明码的位数：2<sup>n</sup> = 1 << n

数据位的位数：2<sup>n</sup>-n-1 = (1<<n)-n-1

## Python实现

simple_example.py 是一个简单的汉明码原理示例。

HammingCode.py 实现了汉明码的编码与解码，不过还没有封装成类。

### HamingCode.py

这里简单说明一下里面的函数功能

hamming_encode(x, n=4)，hamming_decode(x, n=4) 分别是汉明码的编码与解码功能。x是bytes类型的输入，其大小(bit)应该是2<sup>n</sup>-n-1。n是奇偶校验位的位数，应该不小于3。

hamming_encode_by_block(x, n=4)，hamming_decode_by_block(x, n=4) 分别是编码与解码，可以处理任意长度的数据。通过把任意长度的数据按顺序切分成多份同样大小的数据来编码，再合并。其中x是输入数据，应为一个整数。n是奇偶校验位的位数。

