extern s32 setObjectAnimationFrame(s32, s32, s32, s32); /* force animation frame */
extern s32 setAnimationFrame(s32, s32, s32, s32); /* set animation frame if changed */
extern s32 sub_080C31E4(void *, void *, s32); /* _call_via_r2 */

/* Animation command: request frame 2; when the animation reports its finish
 * flag (bit 1), restart that frame, clear the current step's counter byte and
 * run the next command in the stream. */
void sub_0804D5C4(void *arg0)
{
  s32 *stream;
  int stepOff;
  s32 anim;
  s32 sprite;
  void *work;
  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  anim = work + 0x34;
  setAnimationFrame(sprite, anim, 2, 0);
  stepOff = 0x19;
  if (2 & (*((u8 *) (((s8 *) work) + 0x34))))
  {
    setObjectAnimationFrame(sprite, anim, 2, 0);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + stepOff)) = 0;
    stream = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *stream);
  }
}
