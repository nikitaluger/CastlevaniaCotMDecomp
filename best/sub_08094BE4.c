extern u32 D_0810086C[];
extern void sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_08094BE4(u8 *arg0)
{
  u8 *p;
  u8 *q;
  u8 *r2;
  s16 idx;
  u8 *base;
  u32 litbase;
  u8 bz;
  p = *((u8 **)(arg0 + 0xAC));
  q = *((u8 **)(p + 0x04));
  if (sub_0805F9B4((*((s16 *) q)) << 16, (*((s16 *) (q + 0x02))) << 16) == 1)
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  sub_0800168C(arg0, 0, 8, 0);
  r2 = *((u8 **) (arg0 + 0x3C));
  if (r2 == 0)
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((u32 *) (r2 + 0x04)) = (u32) (((*((u16 *) ((*((u8 **) (p + 0x04))) + 0x06))) * 8) + (u32)&D_0810086C[0]);
  {
    struct Z { u32 w; u8 b; };
    struct Z z = {0, 0};
    *((u32 *) (r2 + 0x00)) = z.w;
    bz = z.b;
  }
  {
    u32 orv = ((u16) 0x1000) | (*((u16 *) (arg0 + 0x02)));
    *((u16 *) (arg0 + 0x02)) = (u16) orv;
  }
  idx = 0;
  ;
  arg0[((*((s16 *) (arg0 + 0x22))) * 2) + 0x19] = bz;
  litbase = (u32) 0x08671BB0;
  base = arg0 + 0x18;
  sub_080C31E4(base, arg0 + 0x22, *((u32 *) litbase));
  idx = *((s16 *) (arg0 + 0x22));
  arg0[(idx * 2) + 0x19]++;
  idx = *((s16 *) (arg0 + 0x22));
  base = base + (idx * 2);
  sub_080C31E0(arg0, *((void **) ((*((u32 *) (arg0 + 0x14))) + (base[0] * 4))));
}
