extern void sub_08011368(s32, void *, s32, s32);
extern s32 signedRemainder(s16, s32);
extern s32 sub_08014990(s32);
extern s32 sub_080C364C(s16, s32);
extern void *sub_08024E4C(s32, s32, s32, s32, s32);
extern s32 (*gTrigFuncTable[])(s32);
extern void sub_080C31E4(void *, void *, u32);
inline static int inline_fn(s32 arg0)
{
  return (gTrigFuncTable[0](arg0 + 0x4000) << 4) + 0xFFEC0000;
}

void sub_080245EC(void *arg0)
{
  u8 *self;
  s32 sprite;
  u8 *state;
  u8 *anim;
  u8 *control;
  s32 a;
  s32 angle;
  s32 x;
  s32 y;
  s32 sep_y;
  s16 step;
  self = (u8 *) arg0;
  sprite = *((s32 *) (((u8 *) arg0) + 0x38));
  anim = self + 0x3C;
  state = *((u8 **) anim);
  do { anim = state + 0x34; } while (0);
  control = state + 0x48;
  sub_08011368(sprite, anim, 5, 0);
  if (((u16) signedRemainder(*((s16 *) control), 10)) == 0)
  {
    if (sub_08014990(sprite) < 0)
    {
      s32 a;
      a = sub_080C364C(*((s16 *) control), 10);
      {
        s32 sa;
        s32 base;
        sa = (s16) a;
        sa = (sa << 16) >> 4;
        angle = (u16) ((base = 0xFFFFA000) - sa);
      }
      x = (*((s32 *) (state + 8))) + inline_fn(angle);
      y = (gTrigFuncTable[0](angle) * 20) + 0xFFD80000;
    }
    else
    {
      s32 a;
      a = sub_080C364C(*((s16 *) control), 10);
      angle = (u16) ((((u16) a) << 12) + 0xE000);
      a = *((s32 *) (state + 8)); x = ((gTrigFuncTable[0](angle + 0x4000) << 4) + 0x140000) + a;
      y = (gTrigFuncTable[0](angle) * 20) + 0xFFD80000;
    }
    sep_y = (*((s32 *) (state + 0xC))) + y; y = sep_y;
    sub_08024E4C(x, y, angle, *((s32 *) ((*((u8 **) (state + 0x50))) + 4)), *((s16 *) (state + 0x1c)));
    y = (*((u16 *) control)); *((u16 *) control) = y + 1;
  }
  if ((*((u8 *) anim)) & 2)
  {
    *((u16 *) control) = 0;
    if ((*((s16 *) (state + 0x1c))) == 0x45)
    {
      u32 cb;
      step = *((s16 *) (self + 0x22));
      y = (step * 2); anim = self + y;
      *((u8 *) (anim + 0x17)) = 0;
      cb = *((u32 *) 0x08671BD8);
      ((void (*)(void *, void *, u32)) cb)(self + 0x18, self + 0x22, 0);
    }
    else
    {
      s16 step;
      step = *((s16 *) (self + 0x22));
      *((u8 *) ((self + (step * 2)) + 0x19)) = 0;
      do { sub_080C31E4(self + 0x18, self + 0x22, *((u32 *) 0x08671BB0)); } while (0);
    }
  }
}

