extern void sub_08011368(s32, s32, s32, s32);
extern void sub_080113A8(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Advance the projectile's animation and, once it reports completion (bit 1 of
 * its status byte), switch it to animation 3, clear the current script byte and
 * move on to the next script instruction. */
void sub_08044A1C(void *arg0)
{
  s32 *advanceFunc;
  s32 owner;
  void *projectile;
  s32 animator;
  owner = *((s32 *)((s8 *)arg0 + 0x38));
  projectile = *((void **)((s8 *)arg0 + 0x3C));
  animator = (s32)projectile + 0x34;
  sub_080113A8(owner, animator);
  if (2 & (*((u8 *)((s8 *)projectile + 0x34))))
  {
    sub_08011368(owner, animator, 3, 1);
    *((s8 *)((s8 *)(((*((s16 *)((s8 *)arg0 + 0x22))) * 2) + arg0)) + 0x19) = 0;
    advanceFunc = (s32 *)0x08671BB0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *advanceFunc);
  }
}
