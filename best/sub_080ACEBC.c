s32 sub_08005910(s32 a, s32 b);
s32 sub_080059DC(s32 a, s32 b);
struct Obj
{
  u8 pad0[0x5C];
  s32 x5C;
  u8 pad60[0x0C];
  s32 x6C;
  u8 pad70[0x0C];
  s32 x7C;
  u8 pad80[0x0C];
  s32 x8C;
};
struct Sp10
{
  u8 pad0[0x08];
  s32 x08;
  s32 x0C;
};
struct Unk14
{
  u8 pad0[0x3C];
  struct Sp10 *x3C;
};
struct Arg1
{
  struct Obj *f0;
  void *f4;
  void *f8;
  struct Obj *fC[2];
  struct Unk14 *f14;
};
inline u8 *inline_fn(u8 *arg0)
{
  return arg0 + 0x1C;
}

inline volatile long long inline_fn2(s32 arg0)
{
  return arg0;
}

inline s32 inline_fn23(s32 *arg0)
{
  return *arg0;
}

inline u8 *inline_fn234(u8 *arg0)
{
  return arg0 + 0x18;
}

void sub_080ACEBC(void *arg0, struct Arg1 *arg1)
{
  u8 *new_var6;
  unsigned int new_var;
  struct Sp10 *sp10;
  u8 *new_var12;
  int new_var10;
  u8 *new_var9;
  s32 *base170;
  struct Arg1 *new_var11;
  s32 *base16C;
  u8 *new_var8;
  u8 *new_var7;
  s32 i;
  s32 stk[22];
  long long new_var2;
  volatile int pad;
  u8 *a = (u8 *) arg0;
  u8 *new_var13;
  volatile int new_var14;
  struct Obj *new_var5;
  s32 *new_var4;
  u8 *new_var3;
  stk[0] = (stk[3] = 0);
  stk[1] = 0;
  stk[2] = 0;
  new_var5 = arg1->f0;
  stk[4] = 0;
  new_var10 = new_var5->x7C;
  sp10 = arg1->f14->x3C;
  *((struct Obj **) (a + 0x18)) = (struct Obj *) ((u32) new_var5->x6C);
  stk[3] = 0;
  base170 = (s32 *) (a + 0x170);
  base16C = (s32 *) (a + 0x16C);
  for (i = 0; ((i - 1) + 1) <= 1; i++)
  {
    s32 off = 10 * (2 * i);
    struct Obj *b = *((struct Obj **) (inline_fn234(a) + off));
    if (1)
    {
    }
    *((u8 *) ((a + 0x28) + off)) = 0;
    new_var4 = base170;
    new_var = sub_08005910(b->x6C - (*new_var4), b->x5C - (*base16C));
    *((s32 *) (inline_fn(a) + off)) = new_var;
    {
      s32 v = sub_080059DC((*base16C) - b->x5C, (*new_var4) - b->x6C);
      new_var8 = a + 0x20;
      *((s32 *) (new_var8 + off)) = v;
      new_var7 = a + 0x24;
      *((s32 *) (new_var7 + off)) = v;
      new_var = 0x44;
    }
  }

  new_var11 = arg1;
  {
    stk[0] = *((s32 *) (((u8 *) arg1->f4) + 0x8C));
    stk[19] = 0;
    new_var6 = (u8 *) arg1->f8;
    stk[1] = *((s32 *) (new_var6 + 0x8C));
    if (1)
    {
      {
        unsigned int oi;
        for (oi = 0; oi <= 1; oi++)
        {
          s32 j;
          new_var10 = stk[19] + 0x50;
          new_var14 = stk[19];
          new_var6 = a + 0x50;
          *((struct Obj **) (a + 0x2C)) = (struct Obj *) ((u32) new_var10);
          for (j = 0; j <= 3; j++)
          {
            s32 eoff = stk[19] + (j * 0x14);
            struct Obj *b2 = *((struct Obj **) ((((u8 *) ((oi == 0) ? (arg1->f4) : (arg1->f8))) + 0x8C) + (j * 4)));
            new_var12 = a + 0x4C;
            *((u8 *) (new_var6 + eoff)) = 1;
            *((struct Obj **) ((a + 0x40) + eoff)) = b2;
            *((s32 *) ((new_var3 = a + new_var) + eoff)) = sub_08005910(b2->x7C - (*new_var4), b2->x6C - inline_fn23(base16C));
            {
              s32 v2 = sub_080059DC((*base16C) - b2->x6C, (*new_var4) - b2->x7C);
              if (a)
              {
                *((s32 *) ((a + 0x48) + eoff)) = v2;
                *((s32 *) ((a + 0x4C) + eoff)) = v2;
              }
              else
              {
                *((a + 0x48) + eoff) = v2;
                new_var9 = new_var12;
                *((s32 *) (new_var9 + eoff)) = v2;
              }
            }
          }

          stk[19] = new_var10;
        }

      }
      do
      {
      }
      while (0);
    }
  }
  {
    unsigned long k;
    new_var10 = 0x108;
    for (k = 0; k <= 1; k++)
    {
      s32 off3 = k * 0x3C;
      struct Obj *b3 = ((0, arg1->fC))[k];
      *((struct Obj **) ((a + 0xE0) + off3)) = b3;
      new_var10 = 0xF4;
      *((s32 *) ((a + new_var10) + off3)) = b3->x7C;
      do
      {
        *((s32 *) ((a + new_var10) + off3)) = inline_fn2(b3->x8C);
        i = (unsigned int) b3->x6C;
      }
      while (0);
      new_var9 = a + 0x16C;
      {
        s32 j2;
        for (j2 = 0; j2 <= 2; j2++)
        {
          s32 eoff3 = off3 + (j2 * 0x14);
          new_var13 = (a + 0xE0) + off3;
          new_var2 = b3->x6C - (*((s32 *) new_var9));
          do
          {
            do
            {
              new_var10 = 0xE8;
              *((u8 *) ((a + 0xF0) + eoff3)) = 2;
              *((s32 *) ((a + 0xE4) + eoff3)) = sub_08005910(b3->x7C - (*((s32 *) (a - (-0x170)))), new_var2);
              {
                volatile unsigned char v3 = sub_080059DC((*((s32 *) (a + 0x16C))) - i, (*((s32 *) (a + 0x170))) - b3->x7C);
                *((s32 *) ((a + 0xEC) + eoff3)) = (*((s32 *) ((a + new_var10) + eoff3)) = v3);
              }
            }
            while (0);
            do
            {
            }
            while (0);
          }
          while (0);
          b3 = *((struct Obj **) new_var13);
        }

      }
    }

  }
  *((struct Unk14 **) (a + 0x158)) = new_var11->f14;
  *((u8 *) (a + 0x168)) = 3;
  *((s32 *) (a + 0x15C)) = sub_08005910(sp10->x0C - (*((s32 *) (a + 0x170))), sp10->x08 - (*((s32 *) (a + 0x16C))));
  {
    s32 vf = sub_080059DC((*((s32 *) (a + 0x16C))) - sp10->x08, (*((s32 *) (a + 0x170))) - (*sp10).x0C);
    *((s32 *) (a + 0x160)) = vf;
    *((s32 *) (a + 0x164)) = vf;
  }
}

