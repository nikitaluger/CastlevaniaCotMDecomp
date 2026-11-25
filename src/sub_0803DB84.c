s32 sub_08011368(s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
inline s8 *asBytePtr(void *arg0)
{
  return (s8 *) arg0;
}

/* Update this entity's attached object: play animation frame 9, clear its
 * timer when flag 1 is set, and on flag 4 switch to frame 0xD and run its
 * update script. */
void sub_0803DB84(void *arg0)
{
  s32 animState;
  s8 *flags;
  s32 *animTable;
  s32 owner;
  void *attached;
  owner = *((s32 *) (((s8 *) arg0) + 0x38));
  attached = *((void **) (asBytePtr(arg0) + 0x3C));
  animState = attached + 0x34;
  sub_08011368(owner, animState, 9, 0);
  flags = asBytePtr(attached) + 2;
  if (1 & (*((u16 *) (((s8 *) attached) + 2))))
  {
    *((s32 *) (((s8 *) attached) + 0x10)) = 0;
  }
  if (4 & (*((u16 *) flags)))
  {
    sub_08011368(owner, animState, 0xD, 0);
    *((s8 *) (asBytePtr(((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0) + 0x19)) = 0;
    animTable = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *animTable);
  }
}
