s32 setObjectAnimation(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Play animation 0x62 on the actor; at script step 0x8C, set the enemy's +0x14
 * value to 0x10000 (and its vertical speed) and step the script on. */
void sub_080B47E0(void *arg0)
{
  s32 *eventPtr;
  int unused;
  s32 anim;
  s32 actor;
  void *enemy;
  actor = *((s32 *) (((u8 *) arg0) + 0x38));
  enemy = *((void **) (((u8 *) arg0) + 0x3C));
  anim = enemy + 0x34;
  setObjectAnimation(actor, anim, 0x62, 1);
  sub_08011528(actor, anim);
  if ((*((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0x8C)
  {
    *((s32 *) (((u8 *) enemy) + 0x14)) = 0x10000;
    *((s8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    eventPtr = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *eventPtr);
  }
}
