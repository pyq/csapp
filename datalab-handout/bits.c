/* 
 * CS:APP Data Lab 
 * 
 * Wei Li (weili1)
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* De Morgan's laws */
  return ~((~x)|(~y));
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x) + 1;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int mask = 0xaa | (0xaa << 8);
  mask = mask | (mask << 16);
  return !((mask | x) + 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int m1,m2,m4;
  m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  m4 = 0x0f | (0x0f << 8);
  m4 = m4 | (m4 << 16);
  x = (x & m1) + ((x>>1) & m1);
  x = (x & m2) + ((x>>2) & m2);
  x = (x+(x>>4)) & m4;
  x = x + (x>>8);
  x = x + (x>>16);
  return x & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask,t1,shift_num,sign;
  sign = (~(!!n)) + 1;
  shift_num = ((~n)+33);
  t1 = x >> n;
  mask = ((t1>>shift_num)<<shift_num) & sign;
  return mask ^ t1;
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return !!(x>>31);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int sx = x >> 31;
  int sy = y >> 31;
  /* x > y => x-y-1 >= 0 => x+(~y)>=0 */
  /*
  int tmp_res = !((x + (~y)) >> 31); // if x > y, 1 else 0
  int same_sign = !(sx ^ sy); // 0 if same sign, -1 otherwise
  int not_equal = !!(x ^ y); // 0 if equal, 1 otherwise
  int x_greater = (!sx) & sy;  // 1 if x>0, y<0; 0 otherwise
  return not_equal & (x_greater | (same_sign & tmp_res));*/

  // optimized(remove one !)
  /*
  int tmp_res = ((x + (~y)) >> 31);
  int same_sign = (sx ^ sy);
  int not_equal = !!(x ^ y); // 0 if equal, 1 otherwise
  int x_greater = (!sx) & sy;  // 1 if x>0, y<0; 0 otherwise
  return not_equal & (x_greater | !(same_sign | tmp_res));*/

  // optimized
  int tmp_res = ((x + (~y)) >> 31);
  int same_sign = (sx ^ sy);
  int not_equal = !(x ^ y); // 0 if equal, 1 otherwise
  int x_greater = sx | !sy;  // 1 if x>0, y<0; 0 otherwise
  return !(not_equal | (x_greater & (same_sign | tmp_res)));
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int minusOne = ~0;
  int isNeg = x >> 31; /* -1 if is neg, 0 if >=0 */
  int isZero = !x; /* 1 if is zero, 0 otherwise */
  int v = x & (x+minusOne);  /* 0 if power of 2. */
  /* neg: -1, 0, 1;
   * pos-p2: 0, 0, 0;
   * pos-not-p2: 0, 0, 1;
   * zero: 0, 1, 0*/
  return !(isNeg | isZero | v);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* int minusOne = ~0; */
  /* int maxv = 1<<(n+minusOne); */
  /* int minvMinusOne = ~maxv; */
  /* int neg_x = (~x)+1; */
  /* int sign = (x>>31); /1* -1 if <0, 0 otherwise *1/ */
  /*        // <0, then minv <= x */
  /* return (sign & (!!((minvMinusOne + neg_x)>>31))) | */
  /*        // >= 0, then  x <= maxv */
  /*        (~sign & (!(maxv + neg_x)>>31)); */
  
  int mask = x >> 31;
  return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* x : 0 or other */
  int boolv = !x; /* 1 or 0 */
  int mask = ~boolv + 1; /* -1 or 0 */
  return (~mask & y) | (mask & z);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  /*x : >=0 or < 0 */
  int sign = (x>>31); /* 0 or -1 */
  int minusOne = ~0;
  int neg_v = minusOne << 31;
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  x |= (x >> 8);
  x |= (x >> 16);
  x = x & ~(x >> 1);
  /* sign 0 -> x
   * -1 -> neg_v
   *  */
  return (sign & neg_v) | (~sign & x);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int e = 0x4e800000; // ((127+30) << 23);
  int mask, halfValue, lastDigits;
  if (x == 0) return 0;
  if (x == 0x80000000) { // (1<<31)
    return 0xcf000000;  // ((127+31)<<23) | (1<<31)
  }
  if (x < 0) {
    x = -x;
    e = 0xce800000; // (1<<31) + e;
  }

  while (!(x&0x40000000)) { // 1<<30
    x <<= 1;
    e -= 0x800000; // (1<<23);
  }
  
  // round to even
  mask = 0xFF;
  halfValue = 0x40;
  lastDigits = x & mask;
  if (lastDigits != halfValue) {
    e += (lastDigits & halfValue) >> 6; // calculate carry
  }
  return ((x >> 7) & 0x7FFFFF) + e;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  int tmp = uf & 0x7FFFFFFF;
  if (tmp > 0x7F800000) return uf;
  return tmp;
}
