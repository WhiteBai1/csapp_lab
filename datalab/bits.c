/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

// #include <unistd.h>
#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int result = ~(~(~x & y) & ~(x & ~y));
  return result;
}
// 德摩根定律：x|y = ~(~x&~y)
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { return 1 << 31; }
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int y = x + x;
  int result1 = y + 2;
  return !result1 & !!(x + 1) & !!y;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int y = 0xAA;
  int result = 0;
  y = y | (y << 8);
  y = y | (y << 16);

  result = x & y;
  result = result ^ y;

  return !result;
}
// 可以自定义数字，利用按位与、按位或等提取有关位数；注意扩展字宽的方法；
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int y = ~x + 1;
  return y;
}
// 取反加一，与溢出和从0计数有关
//  3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int result1 = x + (~0x30 + 1);
  int result2 = x + (~0x39);
  int tmp = 0x80;
  tmp = tmp << 8;
  tmp = tmp << 16;
  result1 = result1 & tmp; // 0
  result2 = result2 & tmp; // 1

  return (!result1) & !!result2;
}
// 利用减法判断正负；没有 "-" 采取加法取负；注意0x39是包含在内的；
// 都要转为bool值判断；
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int tmp = !x; // x!=0,tmp =0; x==0,tmp=1;
  int result1, result2;
  tmp = ~0 + tmp;     // x!=0,tmp=0xFFFFFFFF; x==0,tmp =0x00000000;
  result1 = z & ~tmp; // x!=0,tmp=0,result1=0; x==0,tmp = 0xfffff,result1=z;
  result2 = y & tmp;  // x!=0,result2=y; x==0,reslut2=0;
  return result1 | result2;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sign_x, sign_y, sign;
  int tmp = 0x1;
  int result1, result2;
  tmp = tmp << 31;

  sign_x = x & tmp; // 为负时，sign=1；
  sign_y = y & tmp;
  sign = !(sign_x ^ sign_y); // 同号 sign=1；异号 sign=0；
  // 同正同负；x<=y,返回1；
  result1 = x + (~y) + 1; // x<=y, result1为负，否则为正；
  // x、y相等，!result1返回1；
  result1 = ((!!(result1 & tmp)) | (!result1)) & sign;
  // x<=y,result1 & tmp!=0,result1=1; x>y,result1=0;
  // 异号
  result2 = (!(sign_x)) | sign;
  // x为负，!(sign_x)=0；result2=0时，x<y;
  return result1 | !result2;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int result1, sign;
  sign = 0x1;
  sign = sign << 31;
  // 判断是否为0；
  result1 = x | (~x + 1);   // x=0，sign=0; x!=0，sign=1；
  result1 = sign & result1; // x=0,result =0; x!=0,result =0x80000000;
  // result1 = sign ^ result1; // x=0,result =0x80000000; x!=0,result=0x0;
  result1 = result1 >> 31; // x=0,result =0;x!=0,result=0xffffffff;
  result1 += 1;            // x=0,result =1;x!=0,result=0x0;
  return result1;
}
// 不能引入1的布尔值；~0+1 和 0 的符号位都为0；
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int sign = x >> 31; // x>=0,x=0x00000000;x<0,x=0xffffffff;
  int bit_16, bit_8, bit_4, bit_2, bit_1, bits;
  x = x ^ sign; // x>=0,x不变； x<0,x取反；

  bit_16 = !!(x >> 16); // 二分法判断最高位在上半段还是下半段；
  x = x >> (bit_16 << 4); // 移位，二分继续检查
  bit_8 = !!(x >> 8);
  x = x >> (bit_8 << 3);
  bit_4 = !!(x >> 4);
  x = x >> (bit_4 << 2);
  bit_2 = !!(x >> 2);
  x = x >> (bit_2 << 1);
  bit_1 = !!(x >> 1);
  bits = (bit_16 << 4) + (bit_8 << 3) + (bit_4 << 2) + (bit_2 << 1) + bit_1 +
         1 + (!!x);
  return bits;
}
// 先将负数取反，判断最高1在哪位，再加一；
//  float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int sign, expo, frac, result;
  sign = (0x1 << 31) & uf;  // 保存sign;
  expo = (uf >> 23) & 0xFF; // 提取expo;
  frac = (0xFF | (0xFF << 8) | (0xFF << 15)) & uf;
  // 非数
  if (expo == 0XFF)
    return uf;
  // 正规数 expo！=0；
  if (expo != 0) {
    expo = (expo + 1) & 0xFF;
    // result = (-1) ^ sign * (1 + frac / 23) * 2 ^ (expo - 127);
    result = sign + (expo << 23) + frac;
  } else {
    // 非正规数，要求E=0，不能动阶码，直接动尾数；
    frac = frac << 1;
    // result = (-1) ^ sign * (frac / 23) * 2 ^ (expo - 126);
    result = sign + (expo << 23) + frac;
  }
  return result;
}
// 拆成 sign|exponent|fraction 分别*2
// 正规数   1001.0101可以表示成 + 1.0010101 * 2^3；
// 0.001011 可以表示成 + 1.011 *2^-3
// 即正规数的表示：
// expo位指数（即1.0010101 *2^3中的3）；e也分正负
// frac为尾数（即1.0010101 * 2^3中的1.0010101）
// x=(-1)^S * 1.M * 2^(E-127)
// 非正规数：0.00110001101001 * 2^(−126)
// 定义非正规数的目的是：使最小正规数和0之间更平滑
// (-1)^S * 0.M * 2^(E-126)；E=0,M= 00110001101001
// 非数：当E=255，M != 0时，称为非数
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign, expo, frac, result;
  sign = (uf >> 31) & 0x1; // 为负时，sign=1；
  expo = (uf >> 23) & 0xFF;
  frac = (0xFF | (0xFF << 8) | (0xFF << 15)) & uf;
  if (expo == 0xFF)
    return 0x80000000u;
  if (expo == 0) // 非正规数绝对值小于1，直接返回0；
    return 0;
  if (expo != 0) {
    expo = expo - 127;
    if (expo < 0)
      return 0;
    if (expo > 30)
      return 0x80000000u;
    frac = (0x1 << 23) | frac; // 此时尾数已左移了23位，expo还需要-23；
    if (expo >= 23) {
      result = frac << (expo - 23);
    } else {
      result = frac >> (23 - expo);
    }
    if (sign == 1) {
      result = -result;
    }
  }
  return result;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int expo, result;
  if (x > 127)
    return 0x7f800000;
  else if (x >= -126) {
    // 正规数
    expo = x + 127; // 因为真正的指数=expo-127；
    result = expo << 23;
  } else if (x >= (-126 - 23)) {
    // 非正规数，因为x还可以右移23位（尾数）
    result = 1 << (x + 149);
  } else {
    result = 0;
  }
  return result;
}
// 2.0^x 的单精度浮点表示，就是把数值 2^x（符号0，尾数全0,指数为 x+127）编码成
// IEEE‑754 的 32 位 bit pattern。
