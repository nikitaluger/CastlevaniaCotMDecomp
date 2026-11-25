s32 sub_080114DC(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Sprite-step script callback: switch the companion sprite to animation 0x33
 * and refresh it, advance the work state's movement, clear a field when flags
 * 0x201 are set, and restart the script when flag 4 is set. */
void sub_080B460C(void *entity)
{
  int dispatchArg;
  s32 seq;
  s32 sprite;
  void *work;

  sprite = *((s32 *) (((s8 *) entity) + 0x38));
  work = *((void **) (((s8 *) entity) + 0x3C));
  seq = work + 0x34;
  sub_080114DC(sprite, seq, 0x33, 0);
  sub_08011528(sprite, seq);
  sub_08011EE8(work, 0x4000, 0);
  if (0x201 & (*((u16 *) (((s8 *) work) + 2))))
  {
    *((s32 *) (((s8 *) work) + 0x10)) = 0;
  }
  if (4 & (*((u16 *) (((s8 *) work) + 2))))
  {
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = 0;
    dispatchArg = 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + ((unsigned int) 0x22), *((s32 *) dispatchArg));
  }
}
