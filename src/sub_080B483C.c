s32 sub_080114DC(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_0801165C(void *, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Plays looping animation 0x65 on this effect and steps its 2D motion, then
 * subtracts 0x200/frame from its vertical velocity; once that velocity is no
 * longer positive it restarts the step's action byte and moves to the next
 * script step. */
void sub_080B483C(void *arg0)
{
  s32 velocityY;
  int scriptTable;
  s32 animator;
  s32 sprite;
  void *work;
  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  animator = work + 0x34;
  sub_080114DC(sprite, animator, 0x65, 1);
  sub_08011528(sprite, animator);
  sub_0801165C(work, 0);
  velocityY = (*((s32 *) (((s8 *) work) + 0x14))) + 0xFFFFFE00;
  *((s32 *) (((s8 *) work) + 0x14)) = velocityY;
  if (velocityY <= 0)
  {
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptTable = 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) scriptTable));
  }
}
