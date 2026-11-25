/* identical to sub_080172DC (matched), with its names changed by decompdecomp */
s32 sub_08014990(s32);
void sub_0801843C(void);
void sub_080C31E4(void *, void *, u32);
void sub_080008A0(void *, s32);

/* Pick the actor's signed velocity from its facing, then set its animation
 * step, clear its effect flag and refresh the graphics state. */
void sub_08017418(void *arg0)
{
  u8 *p = (u8 *) arg0;
  s32 facing = *((s32 *) (p + 0x38));
  u8 *info = *((u8 **) (p + 0x3C));
  u8 *fx = info + 0x48;
  void **pp;
  u8 zero;
  sub_0801843C();
  if (sub_08014990(facing) > 0)
  {
    *((s32 *) (info + 0x10)) = 0x60000;
  }
  else
    if (p)
  {
    *((s32 *) (info + 0x10)) = (s32) 0xFFFA0000;
  }
  else
  {
    *((s32 *) (info + 0x10)) = (s32) 0xFFFA0000;
  }
  zero = 0;
  *((u16 *) (fx + 0x16)) = 5;
  *((u8 *) ((p + ((*((s16 *) (p + 0x22))) * 2)) + 0x19)) = zero;
  pp = (void **) 0x08671BB0;
  sub_080C31E4(p + 0x18, p + 0x22, (s32) (*pp));
}

void sub_080161F0(void *arg0);
