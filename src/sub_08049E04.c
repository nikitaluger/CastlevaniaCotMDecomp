extern s32 moduloInt(u8 arg0, s32 arg1);
extern void advanceMotion(void *arg0, s32 arg1);
extern void advanceAnimationOffset(void *arg0, void *arg1, void *arg2, void *arg3);
extern void sub_080C31E4(void *arg0, void *arg1, s32 arg2);
void sub_08049E04(void *arg0)
{
  u8 *self = arg0;
  u16 *r6;
  u8 *r5;
  u8 *r8ptr;
  u8 *r7ptr_1;
  u8 *r7ptr_2;
  u8 *p;
  r6 = *((u16 **) (self + 0x38));
  r7ptr_1 = (r5 = *((u8 **) (self + 0x3C)));
  r8ptr = 0x34 + r5;
  r7ptr_2 = r7ptr_1 + 0x48;
  p = (u8 *) (((*((s16 *) (self + 0x22))) * 2) + ((u32) self));
  if ((*((u8 *) (p + 0x19))) <= 0x0E)
  {
    if (moduloInt(*((u8 *) (p + 0x19)), 5) <= 3)
    {
      *r6 = ((*r6) & 0x0FFF) | 0xC000;
    }
  }
  else
    if (moduloInt(*((u8 *) (p + 0x19)), 3) <= 1)
  {
    *r6 = ((*r6) & 0x0FFF) | 0xC000;
  }
  advanceMotion(r5, 0);
  advanceAnimationOffset(r6, r8ptr, r5, r7ptr_2);
  do { if ((*((u8 *) ((((u8 *) self) + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0x1E)
  {
    s32 zero;
    u8 *p3 = *((u8 **) (((u8 *) r5) + 0x28));
    zero = 0;
    *((u8 *) (p3 + 3)) = 1;
    {
      s32 b = (s8) (*((s8 *) (self + 0x70)));
      *((s32 *) (((u8 *) r5) + 0x10)) = (u32) (b * 0xC000);
    }
    *((s32 *) (((u8 *) r5) + 0x14)) = zero;
    *((s32 *) r7ptr_2) = *((s32 *) (((u8 *) r5) + 0x0C));
    *((u8 *) ((((u8 *) self) + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
    {
      s32 *nv = (s32 *) 0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *nv);
    }
  } } while (0);
}
