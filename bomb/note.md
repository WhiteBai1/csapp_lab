## gdb_learn
- [gdb documents](https://sourceware.org/gdb/current/onlinedocs)

### common commands
- `gdb ./filename` 打开gdb调试指定文件
- `run ` 运行 
- `gdb --args ./filename` 传参；或者使用 `run args` 传参
- `b(break) subroutine_name` set breakpoint
- 到达断点，停止运行，显示上下文信息
- `n(next)` 将执行推进到当前函数的下一行
- `s(step)` 进入源代码当前函数
- `si(stepi)` 进入机器代码下一条指令
- `bt(backtrace)` 查看子进程的stack frame
- `p(print) varible_name`打印变量名，检查变量
- `l(list)` 显示周围十行源代码
- `c(continue)` 继续执行程序
- `q` 退出
- `apropos word` search for commands related to "word"... 按关键字搜索相关命令
- `x $register` 将寄存器的值当作内存地址，查看内存区的内容
- `p $register` 查看内存器的数值



## method
- [实验代码来源](https://github.com/XieGuochao/csapp/tree/main/labs)
- [参考：Arthals' ink](https://arthals.ink/blog/bomb-lab)

### preparation
- 先反汇编 objdump -d bomb > bomb.asm
- 建立 `.gitinit` 设置 command lines;
- 需要使 gdb 自动加载 .gdbinit,`(gdb) set auto-load safe-path .`，‘.’指当前路径；再指定文件 `source .gdbinit`
- `set args psol.txt`设置默认文件输入，注意bomb是一行行读取，即输入一个答案必须换行，才能正常运行

- 跳过炸弹，在触发时不爆炸

### phase_1
- 查看反汇编代码，%esi应该为输入的字符串
- 调用 `string_not_equal`，对比答案是否相同
- 查看 `string_not_equal`, 可知其返回值存在%eax中
- `test a b` a&b，`test %eax,%eax`检查%eax为0还是为1；

### phase_2
- 查看反汇编代码，`<read_six_number>`应该是要输入六个数字
- `<read_six_number> `最后 `cmp $0x5,%eax`,相等则跳过 `<explode_bomb>`
- 查找`<__isoc99_sscanf>`的使用，其解析输入字符串，将读取的整数放入提供的寄存器，在返回读取到的整数个数到%eax中
- 注意 `cmp $0x5,%eax` = %eax -$0x5,设立标志位，%eax>5，则ZF=0(结果不为0)，SF==OF(0=0)，满足jg跳转条件；所以 %eax至少为6
- `mov    -0x4(%rbx),%eax ` 
  `add    %eax,%eax`  
  `cmp    %eax,(%rbx)`  
  及  
  `add    $0x4,%rbx`  
  观察可知，rbx是输入的数字，将前一个输入的数字存到%eax中翻两倍，与当前数字比较，若相等，则继续比较下一位，否则爆炸
- 最开始时，%rbx = %rsp +4-4=%rsp  
  %rsp 从`<read_six_numbers>`返回后为1，所以第一个数字为1
  
### phase_3
- `call   400bf0 <__isoc99_sscanf@plt>`  
  `cmp    $0x1,%eax`  
  `jg     400f6a <phase_3+0x27>`  
  `call   40143a <explode_bomb>`  
  `<__isoc99_sscanf@plt>`依旧读取整数，将整数个数放入 %eax中，则至少输入两个整数
- 最先输入数据占用当用栈的最低位置
- `lea    0xc(%rsp),%rcx`  
  `lea    0x8(%rsp),%rdx`  
  输入的数据会存在 $rsp+8 和 $rsp+12中
- `cmpl   $0x7,0x8(%rsp)`  
  第一个参数要小于7，否则会跳转到炸弹  
  之后会跳转到一个switch中  
- 第一个参数为1时，跳转到  
  `mov    $0x137,%eax`  
  `cmp    0xc(%rsp),%eax`  
  ` je     400fc9 <phase_3+0x86>`  
  第二个参数与 0x137 比较，相等则跳过炸弹
  其他分支同理

### phase_4
- 依旧要求输入两个数字
- `cmpl   $0xe,0x8(%rsp)`  
  `jbe    40103a <phase_4+0x2e>`
  且要求第一个数小于等于15
- `test   %eax,%eax` 为了不跳转到炸弹，要求%eax=0；查看func4
- `mov    $0x0,%eax` 则要走这条分支，打开视图，更加清楚，即前面要求`cmp    %edi,%ecx`
- ecx = edx-esi = e-0;  
  `shr    $0x1f,%ecx`，再右移31为0  
  `add    %ecx,%eax`，加eax = 14
  `sar    $1,%eax`，算数右移一位为7  
  `cmp    %edi,%ecx`  
  `jle    400ff2 <func4+0x24>` 要求edi（第一个参数）大于等于7
- `mov    $0x0,%eax`，跳转到这里后，为不使炸弹爆炸  
  `cmp    %edi,%ecx`  
  `jge    401007 <func4+0x39>` 要求edi（第一个参数）小于等于7
- 所以第一个参数为7
- 第二个参数很简单，为0

### phase_5
- %cl 是 %rsp 的低八位
- %edx 是 %rdx 的低32位视图；两者指向同一片物理寄存器。
- %dl 是 %rdx 的最低8位寄存器视图
- `call   40131b <string_length>`  
  `cmp    $0x6,%eax` 可知要输入6个字符
- `movzbl (%rbx,%rax,1),%ecx`  
  `mov    %cl,(%rsp)`  
  `mov    (%rsp),%rdx`  
  `and    $0xf,%edx`  
  提取rdx的二进制后四位


### phase_6
- 可参考[参考：Arthals' ink](https://arthals.ink/blog/bomb-lab)
- 注意：本版实验代码还做了 `x = 7-x`的映射，与参考版本略有不同；另外最后的顺序是递减




## question
- the different of `code` and `touch`?


## assembly syntax
- `call b` 将下一条指令地址（即调用函数返回的地址）自动压入栈中，再跳到被调函数
- `test a b` a&b
- `jg` Jump if Greater,有符号跳转，ZF == 0 且 SF == OF
- `ja` Jump if Above,无符号跳转，CF == 0 且 ZF == 0
- `jbe` Jump if Below or Equal,无符号跳转，CF == 1 或 ZF == 1
- `shr` 逻辑右移 把 d 里的值整体向低位移动s，空出来的高位补 0；最右边被移出的位会写入进位标志 CF
- `sar` 算数右移，补位复制最高位