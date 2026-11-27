extern void advanceMotion(void *, s32);
extern void sub_08044FD4(s32, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Launch the projectile (spawn id 0x2D82) and run its vertical hit test; once
 * the projectile is moving upward, clear its hit flag and the current script
 * byte and move on to the next script instruction. */
void sub_08044930(void *arg0)
{
  s32 *advanceFunc;
  void *projectile;
  void *hitState;
  projectile = *((void **)((s8 *)arg0 + 0x3C));
  hitState = (s8 *)projectile + 0x48;
  advanceMotion(projectile, 0x2D82);
  sub_08044FD4(0, arg0, projectile, hitState);
  if (*((s32 *)((s8 *)projectile + 0x14)) > 0)
  {
    *((s8 *)((s8 *)hitState + 5)) = 0;
    *((s8 *)((s8 *)(((*((s16 *)((s8 *)arg0 + 0x22))) * 2) + arg0)) + 0x19) = 0;
    advanceFunc = (s32 *)0x08671BB0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *advanceFunc);
  }
}
