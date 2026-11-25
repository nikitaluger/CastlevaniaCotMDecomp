extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u8 D_02021E90[];
extern s32 D_080DFF9C[];
extern s32 D_080DFFB0[];
extern u32 D_08671BD0;
s32 sub_08084500(void *a, void *b, void *c);
void sub_080C31E8(void *a, void *b, s32 c, u32 d);
void *sub_0806D24C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
void sub_08084AD0(void *a);
void sub_0806A7AC(void *a, void *b, s32 c);
void sub_08085440(void *a, void *b, void *c, s32 d);
inline u8 *inline_fn(void *arg0)
{
  return (u8 *) arg0;
}

inline u16 *inline_fn2(u8 *arg0)
{
  return (u16 *) arg0;
}

s32 sub_0806B66C(void *a, void *b, void *c)
{
  u8 *r5 = inline_fn(a);
  s32 *new_var3;
  int new_var2;
  void *r10 = b;
  s16 new_var;
  u8 *r6 = inline_fn(c);
  u8 *r9 = D_02025368;
  u32 r8;
  if ((*((u32 *) (r6 + 0x9C))) != 4)
  {
    u8 *p25 = D_02025FF0;
    if ((*((u32 *) (p25 + 0x24))) != 0)
    {
      if (((*((u16 *) (p25 + 0x28))) & (*((u16 *) (r9 + 0x3BC)))) == 0)
      {
        if (r5)
        {
          goto ret0;
        }
        else
        {
          goto ret0;
        }
      }
    }
    else
    {
      u8 *p21 = D_02021E90;
      if (((*inline_fn2(p21 + 0x146C)) & (*((u16 *) (r9 + 0x3BC)))) == 0)
      {
        goto ret0;
      }
    }
    *((u32 *) (r6 + 0xC4)) = (r8 = (u16) sub_08084500(r5, r10, r6));
    if (r8 != 0)
    {
      s16 idx = *((s16 *) (r5 + 0x22));
      *inline_fn((r5 + (idx * 2)) + 0x19) = 0;
      {
        u32 *nv = &D_08671BD0;
        sub_080C31E8(r5 + 0x18, r5 + 0x22, r8, *nv);
      }
      return 2;
    }
    if ((*((u32 *) (r6 + 0x48))) == 1)
    {
      u8 *r7 = r9 + 0x2D8;
      new_var = 0x150C;
      if ((*r7) != 0)
      {
        s32 val = (*((s16 *) (r9 + 0x2D4))) + (*((s32 *) (D_02025FF0 + new_var)));
        u8 bval = *r7;
        unsigned char r4 = ((u32) (bval - 1)) * 4;
        s16 s1 = *((s16 *) (r9 + 0x8C));
        u32 off = ((u32) (((short) ((s1 * 4) + s1)) * 4)) + r4;
        new_var2 = 7;
        if (val >= D_080DFFB0[off >> 2])
        {
          void *res = sub_0806D24C((s32) r5, 0x25, new_var2, *(new_var3 = &D_080DFF9C[r4 >> 2]));
          if (res != 0)
          {
            *((u16 *) (inline_fn(res) + 0x7C)) = bval;
            *((u16 *) (inline_fn(res) + 0x84)) = r8;
            sub_08084AD0(r5);
            sub_0806A7AC(r10, r6, 0x18);
            {
              s16 idx = *((s16 *) (r5 + 0x22));
              *inline_fn((r5 + (idx * 2)) + 0x19) = 0;
            }
            {
              u32 *nv = &D_08671BD0;
              sub_080C31E8(r5 + 0x18, r5 + 0x22, 0x11, *nv);
            }
            return 1;
          }
        }
      }
    }
    *((u32 *) (r6 + 0x70)) = 1;
    *((u32 *) (r6 + 0x48)) = 0;
    sub_08085440(r5, r10, r6, 0x0B);
    {
      u32 *pp = (u32 *) (r6 + 0x130);
      *((u16 *) (((u8 *) (*pp)) + 0x0E)) = *((u16 *) (r9 + 0x2E0));
      *((u16 *) (((u8 *) (*pp)) + 0x16)) = 0x1E;
    }
    {
      s16 idx = *((s16 *) (r5 + 0x22));
      *inline_fn((r5 + (idx * 2)) + 0x19) = 0;
    }
    {
      u32 *nv = &D_08671BD0;
      sub_080C31E8(r5 + 0x18, r5 + 0x22, 0x0B, *nv);
    }
    return 1;
  }
  ret0:
  return 0;

}

