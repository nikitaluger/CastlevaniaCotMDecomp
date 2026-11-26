extern u32 sub_0806D518(void *, void *, void *);
extern void sub_08005E80(u32);
extern void sub_080C31E8(void *, void *, u32, u32);
extern s16 sub_080C364C(u32, s16);
extern void sub_08072334(void *, u32, u32, void *);
extern void sub_080722E0(void *, u8);
extern void sub_080168C4(void);
extern void *sub_080168F8(void);
extern void sub_08003740(void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806D330(void *, void *);
extern void sub_080C31E0(void *, u32);
extern u8 *gMainWorkspace;
extern u32 *D_08671BD0;
inline static u8 *inline_fn(u8 *arg0)
{
  return arg0 + 0x18;
}

inline static u8 *inline_fn2(u8 *arg0)
{
  return *((u8 **) (arg0 + 0x2C));
}

void sub_0807B918(u8 *arg0)
{
  u32 **__base_D_08671BD0;
  u8 **__base_D_02025FF0;
  u32 *__repair_probe_;
  u8 *self;
  u8 *p9;
  u8 *p9_w1;
  u8 *p10;
  u8 *p8;
  u8 *pc_w1;
  u8 *pc_w2;
  u32 r4;
  u32 r4_w2;
  u32 __repair_result_r4;
  u16 *new_var3;
  unsigned int new_var4;
  u8 *new_var6;
  s16 *new_var5;
  u32 v;
  u32 v_w1;
  self = arg0;
  p9 = *((u8 **) (self + 0x6C));
  p10 = p9 + 4;
  p8 = *((u8 **) (self + 0x38));
  new_var5 = (s16 *) (p8 + 4);
  __repair_result_r4 = sub_0806D518(self, p8, p10);
  if (__repair_result_r4 != 0)
  {
    return;
  }
  if ((--(*((u32 *) (p10 + 0x14)))) == 0)
  {
    sub_08005E80(0x144);
  }
  new_var6 = p10;
  if ((--(*((u32 *) (p10 + 0x48)))) == 0)
  {
    u32 *p08671BD0;
    *((u8 *) (inline_fn2(p10) + 1)) = 0;
    p9 = self + ((*((s16 *) (self + 0x22))) * 2);
    *((u8 *) (p9 + 0x19)) = 0;
    __base_D_08671BD0 = &D_08671BD0;
    p08671BD0 = *__base_D_08671BD0;
    sub_080C31E8(self + 0x18, self + 0x22, 4, *p08671BD0);
    *((u8 *) (p9 + 0x19)) = (*((u8 *) (p9 + 0x19))) + 1;
    pc_w1 = inline_fn(self) + ((*((s16 *) (self + 0x22))) * 2);
    v = *((u8 *) pc_w1);
    r4 = *((u32 *) ((*((u32 *) (self + 0x14))) + (v * 4)));
    sub_080C31E0(self, r4);
  }
  else
    if ((*((*((u8 **) (p10 + 0x4C))) + 1)) != (*((u8 *) (p9 + 0x54))))
  {
    u32 *p08671BD0;
    pc_w2 = self + ((*((s16 *) (self + 0x22))) * 2);
    p08671BD0 = *__base_D_08671BD0;
    *((u8 *) (pc_w2 + 0x19)) = (__repair_probe_ = p08671BD0, 0);
    do
    {
      do
      {
        do
        {
          sub_080C31E8(inline_fn(self), self + 0x22, 2, *__repair_probe_);
        }
        while (0);
      }
      while (0);
    }
    while (0);
    *((u8 *) (pc_w2 + 0x19)) = (*((u8 *) (pc_w2 + 0x19))) + 1;
    pc_w1 = inline_fn(self) + ((*((s16 *) (self + 0x22))) * 2);
    v_w1 = *((u8 *) pc_w1);
    __repair_result_r4 = *((u32 *) ((*((u32 *) (self + 0x14))) + (v_w1 * 4)));
    sub_080C31E0(self, __repair_result_r4);
  }
  else
  {
    s16 a;
    if ((a = *new_var5) > 0x100)
    {
      *((u16 *) (p8 + 4)) = (*((u16 *) (p8 + 4))) - 0x40;
      *((u16 *) (p8 + 6)) -= 0x40;
      new_var3 = (u16 *) (inline_fn2(p10) + 6);
      *new_var3 = sub_080C364C(0x1600, *((s16 *) (p8 + 4)));
      *((u16 *) (inline_fn2(new_var6) + 8)) = sub_080C364C(0x1600, *((s16 *) (p8 + 6)));
    }
    {
      u8 *p4c = *((u8 **) (p10 + 0x4C));
      sub_08072334(new_var6, *((u32 *) (p4c + 0xC)), *((u32 *) (p4c + 0x10)), p9 + 0x44);
      sub_080722E0(new_var6, *((u8 *) (p9 + 0x48)));
    }
    *((u32 *) (p9 + 4)) += (((((s32) (*((u32 *) (new_var6 + 0x40)))) >> 8) * (*((s32 *) (new_var6 + 8)))) + 0xFF) >> 8;
    pc_w2 = new_var6;
    *((u32 *) (pc_w2 + 4)) += (((((s32) (*((u32 *) (pc_w2 + 0x40)))) >> 8) * (*((s32 *) (pc_w2 + 0xC)))) + 0xFF) >> 8;
    sub_080168C4();
    if (((*((u32 *) (p10 + 0x54))) == 0) || ((--(*((u32 *) (pc_w2 + 0x54)))) == 0))
    {
      *((u8 *) (p9 + 0x49)) = 2;
    }
    while (sub_080168F8() != 0)
    {
      u8 *q = sub_080168F8();
      if ((*((u32 *) (q + 8))) == (*((u32 *) (pc_w2 + 0x2C))))
      {
        *((u8 *) (p10 + 0x45)) = 8;
        *((u32 *) (new_var6 + 0x54)) = 0x10;
        break;
      }
    }

    __base_D_02025FF0 = &gMainWorkspace;
    *((u16 *) p8) = *((u16 *) (new_var3 = (*__base_D_02025FF0) + 0x18C2));
    sub_08003740(new_var6 + 0x1C);
    sub_0806D588(p8, new_var6);
    p9_w1 = (*__base_D_02025FF0) + 0x10;
    if (((*((u8 *) ((*__base_D_02025FF0) + (new_var4 = 0x173A)))) == 0x1C) || (((*((u8 *) ((*__base_D_02025FF0) + 0x14ED))) != 0) && ((*((u32 *) p9_w1)) != 0)))
    {
      r4_w2 = *((u32 *) (self + 0x24));
    }
    else
    {
      sub_0806D330(self, p8);
      return;
    }
    sub_080C31E0(self, r4_w2);
  }
  return;
}

