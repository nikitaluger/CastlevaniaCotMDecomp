extern void sub_08061ED0(s32, void *, s32);
extern u8 sub_08061CE8(s32, s32);
extern s32 sub_08061D9C(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_080D9AA0[];
extern u8 D_080D9AB0[];
extern u8 D_080D9AC0[];
extern u8 D_080D9B3C[];
extern u8 D_080DABDC[];
extern u16 D_03000830[];
struct S61340
{
  u8 buf[0xB0C];
  u32 f0C;
  u32 f10;
  u32 f14;
  u32 f18;
  u32 f1C;
  u32 f20;
  u32 f24;
  u32 f28;
  u32 f2C;
  u32 f30;
  u32 f34;
  u32 f38;
  u32 f3C;
  u32 f40;
  u32 f44;
  u32 f48;
  u32 f4C;
  u32 f50;
};
void sub_08061340(void *arg0)
{
  struct S61340 s;
  int new_var9;
  u8 new_var8;
  u32 a;
  u32 b;
  char c;
  u32 d;
  u8 *p;
  u8 new_var5;
  u8 t;
  int new_var3;
  int new_var10;
  u8 t2;
  u8 t5;
  u32 new_var;
  u8 *new_var7;
  u8 t7;
  u32 v;
  int new_var6;
  struct S61340 *new_var2;
  u32 new_var4;
  s.f0C = (u32) arg0;
  s.f1C = 0;
  s.f10 = 0;
  sub_08061ED0(*((s32 *) (s.f0C + 0x38)), (void *) s.f0C, 0);
  new_var = s.f14 <= 0x29;
  *((u16 *) (*((u32 **) (s.f0C + 0x3C)))) = D_03000830[3];
  s.f40 = (u32) (&s.buf[0x20]);
  s.f48 = s.f0C + 0x18;
  s.f4C = s.f0C + 0x22;
  s.f10 = (s.f14 = 0);
  new_var10 = 0xF;
  do
  {
    s.f14 = 0;
    p = (u8 *) (s.f40 + (0x2B * s.f10));
    do
    {
      *p = sub_08061CE8(s.f10, s.f14);
      p++;
      s.f14++;
    }
    while (s.f14 <= 0x2A);
    s.f10++;
  }
  while (s.f10 <= 0x40);
  new_var9 = 0x06008000;
  s.f2C = new_var9;
  do
  {
    s.f18 = 0;
    s.f44 = s.f14 << 6;
    new_var = s.f2C;
    s.f3C = s.f14 + 2;
    do
    {
      s.f20 = 0;
      s.f38 = s.f18 + 1;
      v = s.f20;
      s.f50 = new_var + 0x20;
      s.f30 = s.f18 * 2;
      s.f34 = s.f30 + s.f44;
      s.f24 = 0;
      do
      {
        a = ((1 & s.f20) + s.f30) * (new_var3 = 0x2B);
        b = s.f14 + (s.f20 >> 1);
        t = *((u8 *) ((s.f40 + b) + a));
        s.f20 = *((u8 *) (((s.f40 + b) + a) + new_var3));
        new_var5 = D_080D9AC0[0];
        v = *((u8 *) (((s.f40 + b) + a) + 1));
        new_var8 = *(new_var7 = (u8 *) (((s.f40 + b) + a) + 0x2C));
        s.f28 = new_var8;
        c = s.f34 + (*((u32 *) (D_080D9AB0 + s.f24)));
        switch (t)
        {
          case 1:
            t7 = *((u8 *) (D_080DABDC + c));
            t7 >>= 4;
            t5 = *((u8 *) (D_080D9AC0 + (t7 * 4)));
            break;

          case 2:
            t7 = (*((u8 *) (D_080D9B3C + c))) >> 4;
            t5 = *((u8 *) (D_080D9AC0 + (t7 * 4)));
            break;

          default:
            t5 = new_var5;
            break;

        }

        t5 = (t5 | (t5 << 4)) & 0xFF;
        d = *((u32 *) (D_080D9AA0 + s.f24));
        *((u8 *) (&s.buf[d])) = t5;
        *((u8 *) (&s.buf[d + 1])) = t5;
        *((u8 *) (&s.buf[d + 4])) = t5;
        *((u8 *) (&s.buf[d + 5])) = t5;
        *((u8 *) (&s.buf[d + 8])) = t5;
        *((u8 *) (&s.buf[d + 9])) = t5;
        *((u8 *) (&s.buf[d + 0xC])) = t5;
        *((u8 *) (&s.buf[d + 0xD])) = t5;
        t7 = ((*((u8 *) (D_080D9B3C - (-c)))) >> 2) & 3;
        new_var2 = &s;
        new_var6 = t == 2;
        if (t7 != 0)
        {
          if ((s.f20 == 2) || new_var6)
          {
            v = 0x10;
          }
          else
          {
            v = 0x60;
          }
          *((u8 *) (&s.buf[d + 1])) = ((*((u8 *) (&s.buf[d + 1]))) & new_var10) | v;
          *((u8 *) (&s.buf[d + 9])) = ((*((u8 *) (&s.buf[d + 9]))) & new_var10) | v;
          *((u8 *) (&s.buf[d + 0xD])) = ((*((u8 *) (&s.buf[d + 0xD]))) & new_var10) | v;
          t2 = ((t + 1) < ((*new_var2).f20 + 1)) ? ((u8) s.f20) : (t);
          if (t2 == 1)
          {
            s.f1C = 7;
          }
          else
          {
            s.f1C = (t2 == 2) ? (3) : (2);
          }
          if (t7 == 3)
          {
            if ((sub_08061D9C(a, b, 0) == 0) && (t7 == 1))
            {
              *((u8 *) (&s.buf[d + 5])) = ((*((u8 *) (&s.buf[d + 5]))) & new_var10) | v;
            }
            else
            {
              *((u8 *) (&s.buf[d + 5])) = ((*((u8 *) (&s.buf[d + 5]))) & new_var10) | (s.f1C * 0x10);
            }
          }
          else
          {
            *((u8 *) (&s.buf[d + 5])) = ((*((u8 *) (&s.buf[d + 5]))) & new_var10) | ((*new_var2).f1C * 0x10);
          }
        }
        t7 = (*((u8 *) (D_080D9B3C + c))) & 3;
        if (t7 != 0)
        {
          if (((*new_var2).f20 == 2) || (v == 2))
          {
            v = 1;
          }
          else
          {
            v = 6;
          }
          t2 = (t < s.f28) ? ((u8) (*new_var2).f28) : (t);
          if (t2 == 1)
          {
            s.f1C = 7;
          }
          else
          {
            s.f1C = (t2 == 2) ? (3) : (2);
          }
          {
            u32 w = (v * 0x10) | v;
            if (t7 != 2)
            {
              new_var4 = b;
              if (t7 == 3)
              {
                if ((sub_08061D9C(a, new_var4, 1) != 0) || (t7 == 1))
                {
                  w = ((*new_var2).f1C * 0x10) | v;
                }
              }
              else
              {
                w = (s.f1C * 0x10) | v;
              }
              *((u8 *) (&s.buf[d + 0xC])) = w;
            }
            else
            {
              *((u8 *) (&s.buf[d + 0xC])) = ((2 * s.f1C) * 8) | v;
            }
          }
          s.f24 += 4;
        }
      }
      while (v <= 3);
      *((u32 *) 0x040000D4) = (u32) (&s.buf[0]);
      *((u32 *) (0x040000D4 + 4)) = new_var;
      *((u32 *) (0x040000D4 + 8)) = 0x80000010;
      s.f2C = s.f50;
      s.f18 = s.f38;
    }
    while (s.f18 <= 0x1F);
    s.f14 = s.f3C;
    *((u8 *) ((s.f0C + ((*((s16 *) (s.f0C + 0x22))) * 2)) + 0x19)) = 0;
  }
  while (new_var);
  sub_080C31E4((void *) s.f48, (void *) (*new_var2).f4C, *((s32 *) 0x08671BB0));
}

