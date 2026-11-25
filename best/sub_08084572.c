#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
inline int inline_fn()
{
  return 0;
}

s32 sub_08084572(u32 arg1, M2C_UNK arg3)
{
  volatile unsigned char new_var;
  volatile int *new_var6;
  volatile int new_var4;
  volatile int *new_var5;
  volatile int new_var2;
  int new_var3;
  new_var5 = &new_var2;
  new_var6 = new_var5;
  new_var2 = inline_fn();
  new_var3 = new_var;
  if (((*new_var6) && (*new_var5)) && new_var2)
  {
  }
  new_var2 = new_var3;
  new_var4 = *new_var6;
  return new_var4;
  new_var = new_var4;
}

