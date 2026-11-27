s32 scaleByRandom(s32);
s32 sub_080B9824(s32);
s32 sub_080C31E4(void *, void *, s32);

/* Clear the actor's +0x2A flag bit 6 when the object's guard flag at +0x4C is
 * set; once the enemy's +0x48 state check reports completion, reload its timer
 * at +0x08 with a random value in 0x400000..0xAF0000 and step the script on. */
void sub_080B7B78(void *arg0)
{
  void *actor;
  int unused;
  void *enemy;
  actor = *((void **) (((u8 *) arg0) + 0x38));
  enemy = *((void **) (((u8 *) arg0) + 0x3C));
  if ((*((u8 *) (((u8 *) arg0) + 0x4C))) != 0)
  {
    *((u8 *) (((u8 *) actor) + 0x2A)) = (u8) (0xBF & (*((u8 *) (((u8 *) actor) + 0x2A))));
  }
  if (sub_080B9824(*((s32 *) (((u8 *) enemy) + 0x48))) != 0)
  {
    *((s32 *) (((u8 *) enemy) + 8)) = (s32) (scaleByRandom(0x700000) + 0x400000);
    *((s8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    unused = 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) unused));
  }
}
