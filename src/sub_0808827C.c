extern void stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, s32);
extern volatile unsigned short sub_08005E80(s32);
extern void sub_0806D588(void *, void *);
extern s32 sub_0806D6B4(void *);
extern void sub_080C31E4(void *, void *, s32);

/* Tick an airborne actor: when its collision move leaves it in the air, start
 * the fall animation and jump the script step, then run its mover timer and
 * refresh the sprite from the mover. */
void sub_0808827C(void *arg0)
{
  s32 timer;
  s32 work;
  s32 sprite;
  int litAddr;
  void *mover;
  work = *((s32 *) (((s8 *) arg0) + 0x6C));
  mover = work + 4;
  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  if (sub_0806D6B4(mover) == 2)
  {
    startEffectTimer(work + 0x20, 0, 0x08506414);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    litAddr = 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) litAddr));
  }
  timer = (*((s32 *) (((s8 *) mover) + 0x14))) - 1;
  *((s32 *) (((s8 *) mover) + 0x14)) = timer;
  if (timer == 0)
  {
    sub_08005E80(0x69);
    *((s32 *) (((s8 *) mover) + 0x14)) = 0x10;
  }
  stepDelayTimer(work + 0x20, sprite);
  sub_0806D588(sprite, mover);
}
