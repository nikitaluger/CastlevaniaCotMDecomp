extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014EF4(s32);
extern s32 sub_08012A94(s32, s32, s32);
extern s32 sub_080133EC(s32);
extern void sub_08023F34(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_02025FF0[];
extern u32 D_08671BB0[];
extern u32 D_08671BD8[];
struct Arg
{
  u8 pad[0x22];
  s16 idx;
  u8 pad2[0x14];
  void *f38;
  void *f3c;
};
void sub_08022FF8(struct Arg *arg0)
{
  void *r0;
  u8 *p;
  u8 *q;
  u8 *r1;
  s32 bit;
  u32 *new_var;
  s32 res;
  s32 sum;
  s32 c;
  u16 z16;
  u8 z8;
  r0 = arg0->f38;
  p = arg0->f3c;
  r1 = p + 0x34;
  q = p + 0x48;
  sub_08011368(r0, r1, 5, 0);
  {
    u8 *base = D_02025FF0;
    bit = ((*((s32 *) (base + 0x189C))) / 2) & 1;
  }
  if (bit != 0)
  {
    *((u32 *) (q + 0x00)) = 0x10000;
  }
  else
  {
    *((u32 *) (q + 0x00)) = bit;
  }
  c = (*((u16 *) (q + 0x12))) - 1;
  *((u16 *) (q + 0x12)) = c;
  if (((s16) c) >= 0)
  {
    goto end;
  }
  *((s16 *) (q + 0x24)) = (sub_08014EF4(0x1388) != 0) ? (-1) : (1);
  {
    u8 *base = D_02025FF0;
    *((u32 *) (q + 0x14)) = (*((u32 *) (base + 0x1728))) + ((*((s16 *) (q + 0x24))) << 22);
    base += 0x172C;
    res = sub_08012A94(*((s32 *) (q + 0x14)), *((u32 *) base), 0x11);
    sum = (*((u32 *) base)) + res;
    *((u32 *) (q + 0x18)) = sum;
  }
  if (res > 0x00800000)
  {
    goto flip;
  }
  if (sub_080133EC(*((s32 *) (q + 0x14))) == 1)
  {
    goto flip;
  }
  if (((*((s32 *) (q + 0x1C))) - (*((s32 *) (q + 0x14)))) >= 0)
  {
    if (((*((s32 *) (q + 0x1C))) - (*((s32 *) (q + 0x14)))) > 0x00D20000)
    {
      goto flip;
    }
  }
  else
    if (((*((s32 *) (q + 0x14))) - (*((s32 *) (q + 0x1C)))) > 0x00D20000)
  {
    goto flip;
  }
  goto success;
  flip:
  *((u16 *) (q + 0x24)) = -(*((u16 *) (q + 0x24)));

  {
    u8 *base = D_02025FF0;
    *((u32 *) (q + 0x14)) = (*((u32 *) (base + 0x1728))) + ((*((s16 *) (q + 0x24))) << 22);
    base += 0x172C;
    res = sub_08012A94(*((s32 *) (q + 0x14)), *((u32 *) base), 0x11);
    sum = (*((u32 *) base)) + res;
    *((u32 *) (q + 0x18)) = sum;
  }
  if (res > 0x00800000)
  {
    goto fail;
  }
  if (sub_080133EC(*((s32 *) (q + 0x14))) == 1)
  {
    goto fail;
  }
  if (((*((s32 *) (q + 0x1C))) - (*((s32 *) (q + 0x14)))) >= 0)
  {
    if (((*((s32 *) (q + 0x1C))) - (*((s32 *) (q + 0x14)))) > 0x00D20000)
    {
      goto fail;
    }
  }
  else
    if (((*((s32 *) (q + 0x14))) - (*((s32 *) (q + 0x1C)))) > 0x00D20000)
  {
    goto fail;
  }
  goto success;
  fail:
  z16 = 0;
  z8 = 0;
  *((u16 *) (q + 0x0C)) = z16;
  *((u8 *) ((u32)(arg0->idx << 1) + (u32) arg0) + 0x17) = z8;

  {
    u32 *fp = D_08671BD8;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 1, fp[0]);
  }
  goto end;
  success:
  sub_08023F34(*((s32 *) (q + 0x14)), *((s32 *) (q + 0x18)), 0);

  *((u8 *) ((u32)(arg0->idx << 1) + (u32) arg0) + 0x19) = 0;
  new_var = D_08671BB0;
  sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, new_var[0]);
  end:
  ;
}
