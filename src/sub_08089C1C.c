extern s32 stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Low part of the main game state; mode at 0x1C. */
struct S_02025FF0_1C
{
  u8 _0[0x1C];
  u32 mode;
};
extern struct S_02025FF0_1C gMainWorkspace;

/* Scripted object update: once the work animation finishes, restart it from
 * the data at 0x08507DEC, set the game mode to 8, reset the script step and
 * run the next script command; then copy the work position into the sprite. */
void sub_08089C1C(void *arg0)
{
  s32 *litp;
  u8 *entity = (u8 *)arg0;
  u8 *work = *((u8 **)(entity + 0x6C));
  u8 *pos = work + 4;
  u8 *obj = *((u8 **)(entity + 0x38));
  u8 *script = work + 0x20;
  s32 done = stepDelayTimer(script, obj);
  if (done == 0)
  {
    startEffectTimer(script, 0, (void *)0x08507DEC);
    stepDelayTimer(script, obj);
    gMainWorkspace.mode = 8;
    *((u8 *)((entity + ((*((s16 *)(entity + 0x22))) * 2)) + 0x19)) = (u8)done;
    litp = &(*((s32 *)0x08671BB0));
    sub_080C31E4(entity + 0x18, entity + 0x22, *litp);
  }
  sub_0806D588(obj, pos);
}
