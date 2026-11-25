extern s32 sub_080147A4(s32, s32, s32);
extern void sub_080A845C(s32, void *);
extern s32 sub_080C31E0(s32, s32);
void sub_080A860C(s32 arg0, void *arg1)
{
  s32 *r6;
  s32 *r7;
  s32 r9;
  s32 t;
  s32 *g4;
  s32 *g10;
  s32 u;
  s32 tmp;
  s32 r4v;
  s32 b;
  s32 c;
  s32 a;
  s32 *pv;
  if ((*((u8 *) (((u8 *) arg1) + 0xD8))) == 0)
  {
    r9 = *((s32 *) (((u8 *) arg1) + 0xC0));
    t = (*((s32 *) (((u8 *) arg1) + 0xC8))) + (*((s32 *) (((u8 *) arg1) + 0xD0)));
    *((s32 *) (((u8 *) arg1) + 0xC8)) = t;
    u = *((s32 *) (((u8 *) arg1) + 0xCC));
    r6 = (s32 *) (((u8 *) arg1) + 0xC0);
    r7 = (s32 *) (((u8 *) arg1) + 0xC8);
    if ((t > u) || (t < (u = -u)))
    {
      *r7 = u;
    }
  }
  else
  {
    r9 = *((s32 *) (((u8 *) arg1) + 0xC8));
    t = r9 - (*((s32 *) (((u8 *) arg1) + 0xD0)));
    *((s32 *) (((u8 *) arg1) + 0xC8)) = t;
    r7 = (s32 *) (((u8 *) arg1) + 0xC8);
    if (((r9 < 0) && (t > 0)) || ((r9 > 0) && (t < 0)))
    {
      *r7 = 0;
    }
    r6 = (s32 *) (((u8 *) arg1) + 0xC0);
  }
  tmp = (*r6 + *r7) & 0xFFFF;
  *r6 = tmp;
  g4 = (s32 *) 0x08671BFC;
  *((s32 *) (((u8 *) arg1) + 0xA8)) = sub_080C31E0(tmp + 0x4000, *g4);
  *((s32 *) (((u8 *) arg1) + 0xAC)) = sub_080C31E0(*r6, *g4);
  if ((*r7) > 0)
  {
    r4v = (*r6) + 0xFFFFC000;
  }
  else
  {
    r4v = (*r6) + 0x4000;
  }
  r4v = r4v & 0xFFFF;
  g10 = (s32 *) 0x08671BFC;
  pv = r7;
  {
    s32 res = sub_080C31E0(r4v + 0x4000, *g10);
    s32 *dst = (s32 *)((u8 *)arg1 + 0xB4);
    b = *pv;
    if (b < 0) b = -b;
    *dst = (b * res) >> 10;
  }
  {
    s32 res = sub_080C31E0(r4v, *g10);
    s32 *dst = (s32 *)((u8 *)arg1 + 0xB8);
    b = *pv;
    if (b < 0) b = -b;
    *dst = (b * res) >> 10;
  }
  sub_080A845C(arg0, arg1);
  if ((*((u8 *) (((u8 *) arg1) + 0xD8))) == 0)
  {
    t = *r7;
    if (t > 0)
    {
      a = *r6;
      b = *((s32 *) (((u8 *) arg1) + 0xC4));
      c = r9;
      if (sub_080147A4(c, a, b) != 0)
      {
        *((u8 *) (((u8 *) arg1) + 0xD8)) = 1;
      }
    }
    else
    {
      if (t < 0)
      {
        c = *r6;
        b = *((s32 *) (((u8 *) arg1) + 0xC4));
        if (sub_080147A4(a, c, b) != 0)
        {
          *((u8 *) (((u8 *) arg1) + 0xD8)) = 1;
        }
      }
      a = r9;
    }
  }
}
