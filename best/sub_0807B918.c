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
extern void sub_0806D330(void *, void *);
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

void sub_0807B918(u8 *arg0)
{
  u8 *self;
  u8 *p9;
  u8 *p10;
  u8 *p8;
  u8 *tmp;

  self = arg0;
  p9 = *((u8 **) (self + 0x6C));
  p10 = p9 + 4;
  p8 = *((u8 **) (self + 0x38));

  if (checkGlobalStateChange(self, p8, p10) != 0)
  {
    return;
  }

  if (--(*((u32 *) (p10 + 0x14))) == 0)
  {
    playSound(0x144);
  }

  if (--(*((u32 *) (p10 + 0x48))) == 0)
  {
    *((u8 *) (inline_fn2(p10) + 1)) = 0;
    tmp = self + ((*((s16 *) (self + 0x22))) * 2);
    *((u8 *) (tmp + 0x19)) = 0;
    sub_080C31E8(self + 0x18, self + 0x22, 4, *gScriptStepCallbacks);
    tmp = self + ((*((s16 *) (self + 0x22))) * 2);
    *((u8 *) (tmp + 0x19)) = *((u8 *) (tmp + 0x19)) + 1;
    tmp = inline_fn(self) + ((*((s16 *) (self + 0x22))) * 2);
    sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + (*((u8 *) tmp) * 4))));
  }
  else if ((*((*((u8 **) (p10 + 0x4C))) + 1)) != (*((u8 *) (p9 + 0x54))))
  {
    tmp = self + ((*((s16 *) (self + 0x22))) * 2);
    *((u8 *) (tmp + 0x19)) = 0;
    sub_080C31E8(inline_fn(self), self + 0x22, 2, *gScriptStepCallbacks);
    tmp = self + ((*((s16 *) (self + 0x22))) * 2);
    *((u8 *) (tmp + 0x19)) = *((u8 *) (tmp + 0x19)) + 1;
    tmp = inline_fn(self) + ((*((s16 *) (self + 0x22))) * 2);
    sub_080C31E0(self, *((u32 *) ((*((u32 *) (self + 0x14))) + (*((u8 *) tmp) * 4))));
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
      if (t < 0)
      {
        t += 0xFF;
      }
      *((u32 *) (p9 + 4)) += t >> 8;
      t = (((s32) (*((u32 *) (p10 + 0x40)))) >> 8) * (*((s32 *) (p10 + 0xC)));
      if (t < 0)
      {
        t += 0xFF;
      }
      *((u32 *) (p10 + 4)) += t >> 8;
    }

    sub_080168C4();
    if ((*((u32 *) (p10 + 0x54)) == 0) || (--(*((u32 *) (p10 + 0x54))) == 0))
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
      if (*((u32 *) (q + 8)) == *((u32 *) (p10 + 0x2C)))
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
      if ((*((u8 *) (base + 0x173A)) == 0x1C) || ((*((u8 *) (base + 0x14ED)) == 0) && (*((u32 *) (base + 0x10)) != 0)))
      {
        sub_080C31E0(self, *((u32 *) (self + 0x24)));
      }
      else
      {
        sub_0806D330(self, p8);
      }
    }
  }
}
