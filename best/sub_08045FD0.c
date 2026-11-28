extern void stepAnimationTrack(void *, void *);
extern s32 signOf(s32);
extern s32 sub_0801459C(void *, s32);
extern void setSpriteFacingToTarget(void *, s32);
extern void sub_08011EE8(void *, volatile unsigned long long, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void _call_via_r2(void *, void *, void (*)(void *, void *));
extern void (*gMainObjTimerCallbacks)(void *, void *);
extern s16 D_080CF85E[];
void sub_08045FD0(void *arg0)
{
  u8 *arg = (u8 *) arg0;
  void *view = *((void **) (arg + 0x38));
  u8 *work = *((u8 **) (arg + 0x3C));
  u8 *anim = work + 0x34;
  u8 *frame = work + 0x48;
  s32 sign;
  stepAnimationTrack(view, anim);
  {
    u16 f = *((u16 *) (((u8 *) view) + 0x28));
    if ((*((u16 *) frame)) != f)
    {
      *((u16 *) frame) = f;
      *((u8 *) (frame + 2)) = 0x18;
      sign = signOf(*((s32 *) (work + 8)));
      if (((((*((u16 *) (((u8 *) view) + 2))) & 0x10) != 0) && (sign == 1)) || ((((*((u16 *) (((u8 *) view) + 2))) & 0x10) == 0) && (sign == (-1))))
      {
        if (sub_0801459C(work, 0x700000) != 0)
        {
          setAnimationFrame(view, anim, D_080CF85E[*((u8 *) (arg + 0x4C))], 0);
          {
            s32 zero = 0;
            *((u8 *) (frame + 3)) = zero;
            *((u32 *) (work + 0x10)) = zero;
          }
          {
            u8 *step = (u8 *)((u32)(2 * (*((s16 *) (arg + 0x22)))) + (u32) arg);
            step[0x19] = 0;
          }
          {
            void (**callback)(void *, void *) = &gMainObjTimerCallbacks;
            _call_via_r2(arg + 0x18, arg + 0x22, *callback);
          }
          return;
        }
      }
      setSpriteFacingToTarget(view, *((s32 *) (work + 8)));
      if (((*((u16 *) (((u8 *) view) + 2))) & 0x10) != 0)
      {
        *((u32 *) (work + 0x10)) = 0x3000;
      }
    }
  }
  if ((*((u8 *) (frame + 2))) != 0)
  {
    sub_08011EE8(work, (s32) 0x16C1FFFF, 0);
    *((u8 *) (frame + 2)) = (*((u8 *) (frame + 2))) - 1;
  }
}
