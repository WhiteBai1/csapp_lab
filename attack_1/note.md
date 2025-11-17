## note
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
- `touch2` 比较`rdi`和`cookie`，所以我们要将`rdi`设为`cookie`，并在注入后跳转到`touch2`
- 由于我们的输入放在`getbuf`的缓存区，可在`getbuf`时`p $rsp`查看注入代码的起始地址，像`touch1`一样，使缓存区溢出更改跳转地址为缓冲区起始地址，代码执行`mov $0x59b997fa,%edi`
- 将`rdi`设为`cookie`后需要跳转回`touch2`，我们知道调用函数会将返回地址储存到栈顶上，`ret`会跳回该地址，所以我们应将栈顶储存的地址改为`touch2`的，即将`touch2`的地址压入栈中

### touch_3
- 一元 `imul`，第二个因子为`ax/eax/rax`
- 使用绝对地址下断点：`b *0x40188d`  
或使用相对地址：`b *hexmatch+0x41`（更稳，避免地址漂移）
- 与`touch2`相比，有`push``call`等等，会该改变缓存区的值
- 注入代码一开始用rdi保存cookie指针，再将touch3的地址压入栈中  
填充缓冲区，将上一次ret值覆盖为指向注入代码起始地址，执行我们的注入代码  
在调用`touch3`时，`touch3`使用`push`，`call`等，会覆写缓冲区，即将覆写`rdi`里的指针`0x5560f318`，寻找不会被覆写的地址储存cookie，再用rdi储存，即可解决问题