extern s32 sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern s32 sub_08007B3C(void *, s32, s32);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806A884(void *, void *);
extern s32 sub_0806B5B0(void *, void *, void *, void *);
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_02021E90[];
extern u8 D_02023130[];
extern u8 D_02025368[];
struct Globals { u8 pad0[0x24]; s32 f24; u16 f28; u16 f2A; u8 pad2C[0x18A8 - 0x2C]; u8 f18A8; };
extern struct Globals D_02025FF0;
extern u8 D_080E03A0[];
extern s32 D_08671BD0;
#define ANIM(n) sub_080C31E8(self + 0x18, self + 0x22, (n), D_08671BD0)
#define SEQ(v) (self[0x19 + *(s16 *)(self + 0x22) * 2] = (u8)(v))
void sub_080637E4(u8 *arg0)
{
  u8 *r6;
  s32 *r7;
  void *r8;
  u8 *self;
  u8 *new_var;
  u8 *var_r4;
  s32 var_r2;
  volatile unsigned int new_var3;
  u16 var_r1;
  int new_var2;
  u16 t1;
  u16 t4;
  volatile unsigned int t0;
  u8 *new_var4;
  self = arg0;
  r6 = (*(u8 **)(self + 0x6C)) + 4;
  r8 = *((void **)(self + 0x38));
  r7 = (s32 *)r6;
  if (sub_0806C4B4(r6, r6) != 0)
    return;
  sub_0806C5EC(self, r8, r6, r7);
  new_var4 = D_02021E90;
  if (D_02025FF0.f24 != 0)
  {
    if (!(0x10 & D_02025FF0.f2A)) {}
    else goto block_6;
  }
  else if (0x10 & *((u16 *)(new_var4 + 0x146E)))
  {
    block_6:
    t1 = *((u16 *)((u8 *)r8 + 2));
    if (0x10 & t1)
    {
      *((u16 *)((u8 *)r8 + 2)) = 0xFFEF & t1;
      SEQ(t4);
    }
  }
  if (D_02025FF0.f24 != 0)
  {
    if (!(0x20 & D_02025FF0.f2A)) {}
    else goto block_12;
  }
  else if (0x20 & *((u16 *)(new_var4 + 0x146E)))
  {
    block_12:
    t1 = *((u16 *)((u8 *)r8 + 2));
    if (!(0x10 & t1))
      *((u16 *)((u8 *)r8 + 2)) = (0x10 | t1) & 0xFF;
  }
  new_var = r6;
  if (sub_0806B5B0(self, r8, new_var, r7) == 0)
  {
    if (D_02025FF0.f24 != 0)
      var_r1 = D_02025FF0.f2A;
    else
      var_r1 = *((u16 *)(new_var4 + 0x146E));
    if (!(0x80 & var_r1)
        && !(0x4000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0], r7[1] + (new_var2 = 0x10000)))
        && !(0x4000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0] - *(s32 *)(new_var + 0x38), r7[1] + new_var2))
        && (t4 = 0x4000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0] + *(s32 *)(new_var + 0x38), r7[1] + 0x10000), t4 == 0))
    {
      sub_0806A7AC(r8, new_var, 6);
      *((s32 *)(new_var + 0x40)) = 1;
      SEQ(t4);
      ANIM(4);
    }
    else if (D_02025FF0.f24 != 0)
    {
      if (!(*(u16 *)(D_02025368 + 0x3BE) & D_02025FF0.f28)) {}
      else goto block_29;
    }
    else if (!(*(u16 *)(D_02025368 + 0x3BE) & *(u16 *)(new_var4 + 0x146C))) {}
    else
    {
      block_29:
      if (!(sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0], r7[1] + new_var2) & 0x1000)
          && !(0x1000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0] - *(s32 *)(new_var + 0x38), r7[1] + new_var2))
          && !(0x1000 & sub_08007B3C(D_02023130 + (D_02025FF0.f18A8 << 6), r7[0] + *(s32 *)(new_var + 0x38), r7[1] + 0x10000))
          && (t4 = 0x400 & *(u16 *)(new_var + 0xCE), t4 == 0))
      {
        r7[1] += 0x20000;
        *((s32 *)(new_var + 0x40)) = t4;
        *((s32 *)(new_var + 0x4C)) = 1;
        sub_0806A7AC(r8, new_var, 0x10);
        SEQ(t4);
        ANIM(3);
      }
      else
      {
        var_r2 = *((s32 *)(D_080E03A0 + *(s32 *)(new_var + 0x44) * 0x58 + 0x48));
        if (0x10 & *(u16 *)((u8 *)r8 + 2))
          var_r2 = -var_r2;
        r7[2] = var_r2;
        *((s32 *)(new_var + 0x6C)) = 0;
        sub_0806A7AC(r8, new_var, 0x16);
        *((u16 *)(*(u8 **)(new_var + 0x130) + 0x0E)) = *(u16 *)(D_02025368 + 0x2E0);
        sub_08005E80(0x78);
        SEQ(0);
        ANIM(0xF);
      }
    }
  }
  sub_0806AB04(self, r8, new_var, r7);
  if (*(s32 *)(new_var + 0x40) == 0)
  {
    if (*(s32 *)(new_var + 0x4C) == 0 && self[0x18] == 8)
    {
      sub_0806A7AC(r8, new_var, 0x10);
      SEQ(0);
      ANIM(3);
    }
  }
  var_r4 = new_var + 0x28;
  if (sub_08003740(var_r4, r8) == 0)
  {
    sub_0806A7AC(r8, new_var, 5);
    sub_08003740(var_r4, r8);
  }
  sub_0806A884(r8, new_var);
  t0 = (u16)sub_0806BCD8(self, r8, new_var, r7);
  *((s32 *)(new_var + 0xC4)) = t0;
  if (t0 != 0)
  {
    sub_08003740(var_r4, r8);
    SEQ(0);
    new_var3 = *((s32 *)(new_var + 0xC4));
    ANIM(new_var3);
  }
  sub_0806C6B0(self, r8, new_var, new_var);
}
