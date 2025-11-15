## writeup
- 总览`main`，main -> launch -> test -> getbuf
- [参考：小土刀/厚读CSAPP](https://www.wdxtub.com/blog/csapp/thick-csapp-lab-3)  
了解 code-injection 和 ROF(return-oriented programming)

### touch_1
- 输入应在一行，因为读取到换行符截止
- 注意小端法机器

### touch_2
- Linux x86-64传参顺序  
第1-6个：`%rdi` `%rsi` `%rdx` `%rcx` `%r8` `%r9`  
后续参数：使用栈保存