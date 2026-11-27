s32 setObjectModeWord(s32, s32);
s32 sub_080BE6A0(void *);
s32 sub_080BE8D0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Fade-out step: lower the linked effect state's level at +0x40 by 0x300 a
 * frame (clamped at 0) and mirror it into the effect object at +0x34; when it
 * expires stop the companion effect at +0x1C, notify the linked objects and
 * clear this step's script byte, then advance the script. */
void sub_080BA474(void *arg0)
{
  s8 *fade;
  s32 level;
  s32 remaining;
  void *fadeBlock;
  s32 *handlers;
  fadeBlock = (*((s32 *) (((s8 *) arg0) + 0x3C))) + 0x48;
  level = (*((s32 *) (((s8 *) fadeBlock) + 0x40))) + 0xFFFFFD00;
  *((s32 *) (((s8 *) fadeBlock) + 0x40)) = level;
  if (level < 0)
  {
    *((s32 *) (((s8 *) fadeBlock) + 0x40)) = 0;
  }
  fade = (s8 *) fadeBlock;
  sub_080BE8D0(*((s32 *) (fade + 0x34)), *((s32 *) (fade + 0x40)));
  remaining = *((s32 *) (fade + 0x40));
  if (remaining == 0)
  {
    setObjectModeWord(*((s32 *) (fade + 0x1C)), 0);
    sub_080BE6A0(arg0);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = (s8) remaining;
    handlers = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *handlers);
  }
}
