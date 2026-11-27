extern u32 checkGlobalStateChange(void *, void *, void *);
extern void playSound(u32);
extern void sub_080C31E8(void *, void *, u32, u32);
extern s16 divInt32(u32, s16);
extern void turnHeadingToward(void *, u32, u32, void *);
extern void setDirectionVector(void *, u8);
extern void sub_080168C4(void);
extern void *sub_080168F8(void);
extern void stepDelayTimer(void *);
extern void setSpriteScreenPosition(void *, void *);
extern void releaseEntityIfOffscreen(void *, void *);
extern void sub_080C31E0(void *, u32);
extern u8 gMainWorkspace[];
extern u32 gScriptStepCallbacks[];
inline static u8 *inline_fn(u8 *arg0)
{
  return arg0 + 0x18;
}

inline static u8 *inline_fn2(u8 *arg0)
{
  return *((u8 **) (arg0 + 0x2C));
}

inline static u8 *inline_fn23(u8 *arg0, int arg1)
{
  return arg0 + arg1;
}

inline static int inline_fn234(u8 *arg0, u8 *arg1)
{
  return ((*((s16 *) arg0)) * 2) + ((s32) arg1);
}

void sub_0807B918(u8 *arg0)
{
  u8 *tmp2;
  u8 *tmp3;
  u8 *self;
  u8 *p9;
  u8 *p10;
  u8 *p8;
  u8 *temp;
  self = arg0;
  p9 = (void *) (0x6C + ((s32) self));
  temp = *((u8 **) p9);
  p9 = temp;
  p8 = *((u8 **) (self + 0x38));
  p10 = (void *) (4 + ((s32) p9));
  if (checkGlobalStateChange(self, p8, p10) != 0)
  {
    return;
  }
  if ((--(*((u32 *) (p10 + 0x14)))) == 0)
  {
    playSound(0x144);
  }
  if ((--(*((u32 *) (p10 + 0x48)))) == 0)
  {
    u8 *tmp;
    u8 *temp2;
    temp2 = self + 0x18;
    p9 = (void *) (0x22 + ((s32) self));
    *((u8 *) (inline_fn2(p10) + 1)) = 0;
    tmp = (void *) inline_fn234(p9, self);
    *((u8 *) (tmp + 0x19)) = 0;
    sub_080C31E8(temp2, self + 0x22, 4, *gScriptStepCallbacks);
    tmp = (void *) (((*((s16 *) (self + 0x22))) * 2) + ((s32) self));
    *((u8 *) (tmp + 0x19)) = (*((u8 *) (tmp + 0x19))) + 1;
    tmp = inline_fn23(inline_fn(self), (*((s16 *) (self + 0x22))) * 2);
    sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + ((*((u8 *) tmp)) * 4))));
  }
  else
    if ((*((*((u8 **) (p10 + 0x4C))) + 1)) != (*((u8 *) (p9 + 0x54))))
  {
    u8 *tmp;
    tmp = (void *) (((*((s16 *) (self + 0x22))) * 2) + ((s32) self));
    *((u8 *) (tmp + 0x19)) = 0;
    sub_080C31E8(inline_fn(self), self + 0x22, 2, *gScriptStepCallbacks);
    tmp2 = (void *) (((*((s16 *) (self + 0x22))) * 2) + ((s32) self));
    *((u8 *) (tmp2 + 0x19)) = (*((u8 *) (tmp2 + 0x19))) + 1;
    tmp3 = inline_fn(self) + ((*((s16 *) (self + 0x22))) * 2);
    sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + ((*((u8 *) tmp3)) * 4))));
  }
  else
  {
    s16 a;
    a = *((s16 *) (p8 + 4));
    if (a > 0x100)
    {
      *((u16 *) (p8 + 4)) -= 0x40;
      *((u16 *) (p8 + 6)) -= 0x40;
      *((u16 *) (inline_fn2(p10) + 6)) = divInt32(0x1600, *((s16 *) (p8 + 4)));
      *((u16 *) (inline_fn2(p10) + 8)) = divInt32(0x1600, *((s16 *) (p8 + 6)));
    }
    {
      u8 *p4c = *((u8 **) (p10 + 0x4C));
      turnHeadingToward(p10, *((u32 *) (p4c + 0xC)), *((u32 *) (p4c + 0x10)), p9 + 0x44);
    }
    setDirectionVector(p10, *((u8 *) (p9 + 0x48)));
    {
      s32 t;
      t = (((s32) (*((u32 *) (p10 + 0x40)))) >> 8) * (*((s32 *) (p10 + 8)));
      *((u32 *) (p9 + 4)) += t / 0x100;
      t = (((s32) (*((u32 *) (p10 + 0x40)))) >> 8) * (*((s32 *) (p10 + 0xC)));
      *((u32 *) (p10 + 4)) += t / 0x100;
    }
    sub_080168C4();
    if (((*((u32 *) (p10 + 0x54))) == 0) || ((--(*((u32 *) (p10 + 0x54)))) == 0))
    {
      *((u8 *) (p9 + 0x49)) = 2;
    }
    while (1)
    {
      u8 *q = sub_080168F8();
      if (q == 0)
      {
        break;
      }
      if ((*((u32 *) (q + 8))) == (*((u32 *) (p10 + 0x2C))))
      {
        *((u8 *) (p10 + 0x45)) = 8;
        *((u32 *) (p10 + 0x54)) = 0x10;
        break;
      }
    }

    {
      u8 *base = gMainWorkspace;
      *((u16 *) p8) = *((u16 *) (base + 0x18C2));
      stepDelayTimer(p10 + 0x1C);
      setSpriteScreenPosition(p8, p10);
      if (((*((u8 *) (base + 0x173A))) == 0x1C) || (((*((u8 *) (base + 0x14ED))) == 0) && ((*((u32 *) (base + 0x10))) != 0)))
      {
        sub_080C31E0(self, *((u32 *) (self + 0x24)));
      }
      else
      {
        releaseEntityIfOffscreen(self, p8);
      }
    }
  }
}

