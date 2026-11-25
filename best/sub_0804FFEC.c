struct A1
{
  u16 f00;
  u8 _02[0x16];
  s32 f18;
  s16 f1C;
  u8 _1E[2];
  s16 f20;
  u8 _22[0x0E];
  void *f30;
};
struct A23
{
  u8 f00;
  u8 f01;
  u8 _02[2];
  u16 f04;
};
struct E
{
  u8 _0[0x26];
  s16 f26;
  s16 f28;
  u16 f2A;
  u16 f2C;
  s16 f2E;
  s16 f30;
  s16 f32;
};
struct Tbl
{
  u8 _0[6];
  s16 f06;
  u8 _8[0x0C];
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
};
extern struct Tbl D_080CB2B8[];
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02021E90[];
extern struct E *sub_08016238(void *);
extern u32 sub_0806D5F8(u16, u16);
extern void sub_0808D7BC(s32, s32, u32, u32);
extern void sub_080158BC(void *, void *);
inline u32 *inline_fn(unsigned int arg0)
{
  return (u32 *) ((D_02021E90 + arg0) + (((&D_02025FF0)->f18A8 + 1) << 6));
}

inline u16 inline_fn2(int arg0)
{
  return (u16) arg0;
}

inline u8 *inline_fn23(u8 *arg0, int arg1, int arg2)
{
  return (arg0 - arg1) + arg2;
}

void *sub_0804FFEC(void *unused, struct A1 *arg1, struct A23 *arg2, struct A23 *arg3)
{
  struct E *var_r7;
  struct E *var_r8;
  s32 temp_r4;
  s32 temp_r1;
  s32 var_r0;
  struct A1 *new_var3;
  u32 *new_var2;
  s32 var_r2;
  u32 var_r5;
  volatile int off1;
  u32 off2;
  u32 base;
  int new_var4;
  int new_var;
  arg2->f04 = inline_fn2(0xFDFF & arg2->f04);
  arg3->f04 = inline_fn2(0xFDFF & arg3->f04);
  if (arg1->f00 & 1)
  {
    if (1)
    {
      arg2->f01 = (u8) (0xFA & arg2->f01);
      arg3->f01 = (u8) (0xFA & arg3->f01);
    }
    return NULL;
  }
  if (((s16) arg1->f20) > 0)
  {
    arg2->f04 = inline_fn2(arg2->f04 | 0x200);
    arg3->f04 = inline_fn2(arg3->f04 | 0x200);
    sub_08016238(arg2);
    sub_08016238(arg3);
    return NULL;
    var_r7 = (struct E *) arg2;
  }
  var_r8 = sub_08016238(arg2);
  if (var_r8 == NULL)
  {
    var_r8 = sub_08016238(arg3);
    if (var_r8 == NULL)
    {
      return NULL;
    }
    var_r7 = (struct E *) arg3;
  }
  else
  {
    var_r7 = (struct E *) arg2;
  }
  temp_r4 = 0xF & var_r8->f2A;
  temp_r1 = 0xF & var_r7->f2A;
  if ((temp_r1 != 0) && (temp_r4 == temp_r1))
  {
    var_r5 = (sub_0806D5F8(var_r8->f2C, inline_fn2(D_080CB2B8[arg1->f1C].f06 * 8)) << 16) >> 17;
  }
  else
  {
    var_r5 = (sub_0806D5F8(var_r8->f2C, inline_fn2(D_080CB2B8[arg1->f1C].f06 * 8)) << 16) >> 16;
  }
  new_var2 = &var_r5;
  if (((s32) var_r5) <= 0)
  {
    var_r5 = 1;
  }
  if (((s32) var_r5) > 0x270F)
  {
    var_r5 = 0x270F;
  }
  arg1->f18 = arg1->f18 - (*new_var2);
  new_var4 = 6;
  off1 = 0x1278;
  new_var = 0x127C;
  if (((s16) var_r8->f30) < ((s16) var_r7->f30))
  {
    base = (u32) ((s16) var_r7->f30);
    base = (base << 16) + 0x8000;
    var_r2 = (base + (*((u32 *) inline_fn23(D_02021E90, -off1, (D_02025FF0.f18A8 + 1) << new_var4)))) - (((u32) ((s16) var_r7->f26)) << 16);
  }
  else
  {
    base = (u32) ((s16) var_r7->f30);
    base = base << 16;
    base = base + 0x8000;
    var_r0 = *inline_fn(off1);
    var_r2 = (base + var_r0) + (((u32) ((s16) var_r7->f26)) << 16);
  }
  off2 = new_var;
  base = ((u32) ((s16) var_r7->f32)) << 16;
  base = base + 0xFFFF8000;
  sub_0808D7BC(var_r2, (base + (*((u32 *) ((D_02021E90 + off2) + (((D_02025FF0.f18A8 + 1) << 5) << 1))))) - (((u32) ((s16) var_r7->f28)) << 16), var_r5, 0);
  {
    void *fp = arg1->f30;
    if (fp != NULL)
    {
      arg1->f18 = 1;
      *((void **) (((u8 *) fp) + 8)) = var_r8;
    }
  }
  new_var3 = arg1;
  if (((s32) arg1->f18) <= 0)
  {
    switch (temp_r4)
    {
      case 2:
        if ((!(arg1->f00 & 0xC)) && (temp_r1 != 2))
      {
        var_r0 = 4;
      }
      else
      {
        arg1->f18 = 0;
        var_r0 = 1;
      }
        break;

      case 5:
        if ((!(arg1->f00 & (var_r5 = 0xC))) && (temp_r1 != 5))
      {
        arg1->f18 = 1;
        var_r0 = 8;
      }
      else
      {
        arg1->f18 = 0;
        var_r0 = 1;
      }
        break;

      default:
        arg1->f18 = 0;
        var_r0 = 1;

    }

  }
  else
  {
    if (1)
    {
    }
    var_r0 = 2;
  }
  new_var3->f00 = inline_fn2(var_r0 | arg1->f00);
  if (((s16) var_r8->f2E) != 0)
  {
    arg1->f20 = (s16) var_r8->f2E;
  }
  else
  {
    arg1->f20 = 0x1E;
  }
  sub_080158BC(arg1, var_r8);
  return var_r8;
}

