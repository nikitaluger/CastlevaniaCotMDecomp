extern void sub_08005E80(s32);
extern void sub_08011368(void *, void *, u16, u8);
extern s32 sub_080148AC(void *, s32);
extern void *sub_0805FAEC(s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_02027860;
extern u8 D_080CF07C[];
extern u8 D_080CF080[];
extern void *D_08671BB0;
struct S_a { u8 _0[2]; u16 f2; };
void sub_08038984(u8 *arg0)
{
  u8 *new_var;
  void * volatile objs[3];
  u8 *p34;
  s32 sp10;
  void *sp14;
  u8 *a = *((u8 **) (arg0 + 0x38));
  u8 *p = *((u8 **) (arg0 + 0x3C));
  u8 *a18;
  u16 p2;
  u32 i;
  u32 next;
  void *obj;
  s32 off;
  s32 t;
  u8 c;
  p34 = p + 0x34;
  sub_08005E80(0x189);
  if (*((u8 *) (arg0 + 0xA0)) != 0)
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((u8 *) ((*((u8 **) (p + 0x28))) + 1)) = 0;
  sp10 = 0x15;
  new_var = (u8 *) D_080CF07C;
  p2 = *((u16 *) (p + 2));
  if (p2 & 8)
  {
    sp10 = 0x1A;
    ((struct S_a *) a)->f2 |= 0x20;
    *((s32 *) (p + 0xC)) = (*((s32 *) (p + 0xC))) + ((s32) 0xFFF20000);
    a18 = arg0 + 0x18;
    sp14 = arg0 + 0x22;
  }
  else if (p2 & 1)
  {
    sp10 = 0x1F;
    t = *((s32 *) (p + 0x10));
    a18 = arg0 + 0x18;
    sp14 = arg0 + 0x22;
    if (t > 0)
      ((struct S_a *) a)->f2 |= 0x10;
  }
  else
  {
    t = 4;
    t &= p2;
    a18 = arg0 + 0x18;
    sp14 = arg0 + 0x22;
    if (t != 0)
    {
      sp10 = 0x1A;
      if (*((u8 *) (arg0 + 0xA0)) == 0)
      {
        i = 0;
        do
        {
          obj = sub_0805FAEC(D_02027860, 0xEE);
          objs[i] = obj;
          next = i + 1;
          if (obj != NULL)
          {
            c = *((u8 *) (arg0 + 0x4C));
            *((u8 *) (((u8 *) obj) + 0x4C)) = c;
            *((s32 *) (((u8 *) objs[i]) + 0x5C)) = *((s32 *) (p + 8));
            *((s32 *) (((u8 *) objs[i]) + 0x6C)) = (*((s32 *) (p + 0xC))) + ((s32) 0xFFFC0000);
            off = (i + 3) * 8;
            *((s32 *) (((u8 *) objs[i]) + 0x7C)) = sub_080148AC(a, *((s32 *) (new_var + off)));
            *((s32 *) (((u8 *) objs[i]) + 0x8C)) = *((s32 *) (((u8 *) D_080CF080) + off));
            *((u8 *) (((u8 *) objs[i]) + 0xA0)) = (u8) next;
          }
          i = next;
        } while (i <= 2);
      }
    }
  }
  sub_08011368(a, p34, sp10, 0);
  {
    u8 *q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    q[0x19] = 0;
  }
  sub_080C31E4(a18, sp14, *((s32 *) (&D_08671BB0)));
  {
    u8 *q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    q[0x19] = (u8) (q[0x19] + 1);
  }
  {
    u8 b = *((u8 *) (a18 + ((*((s16 *) (arg0 + 0x22))) * 2)));
    sub_080C31E0(arg0, *((void **) ((b * 4) + (*((u32 *) (arg0 + 0x14))))));
  }
}
