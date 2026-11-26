extern s32 sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_08001480(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_1864 { u8 _0[0x1864]; u32 v; };
extern struct S_02025FF0_1864 gMainWorkspace;

/* Scripted object update: once its current animation finishes, start the
 * next script, spawn effect 0x7F attached to the game-state object and run
 * the next script command. */
void sub_08089D40(void *arg0)
{
  s32 *litp;
  u8 *entity = (u8 *)arg0;
  u8 *work = *(u8 **)(entity + 0x6C);
  u8 *pos = work + 4;
  u8 *obj = *(u8 **)(entity + 0x38);
  u8 *script = work + 0x20;
  s32 done = sub_08003740(script, obj);
  if (done == 0)
  {
    sub_08003A6C(script, 0, (void *)0x08507E1C);
    sub_08003740(script, obj);
    sub_08001480(gMainWorkspace.v, 0x7F);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = (u8) done;
    litp = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(entity + 0x18, entity + 0x22, *litp);
  }
  sub_0806D588(obj, pos);
}
