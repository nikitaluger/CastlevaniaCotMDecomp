struct S_02025FF0
{
  u8 _0x000[0x10];
  s32 field10;
  u8 _0x014[0x14ED - 0x14];
  u8 field14ED;
  u8 _0x14EE[0x173A - 0x14EE];
  u8 field173A;
  u8 _0x173B[0x18C2 - 0x173B];
  u16 field18C2;
};
extern struct S_02025FF0 gMainWorkspace;
s32 sub_0806D518(void *, void *, void *);
s32 sub_08003740(void *, void *);
void sub_0806D2F8(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, s32);

/* Spawn a child actor for a script step: after spawn/capacity and timer checks,
 * copy the global display word and the work's position into it, then bail out
 * on bad global state or an out-of-range position before finalizing the child. */
void sub_080773BC(void *actor)
{
  void *work;
  void *position;
  void *child;
  work = *((void **) (((s8 *) actor) + 0x6C));
  position = ((s8 *) work) + 4;
  child = *((void **) (((s8 *) actor) + 0x38));
  if (sub_0806D518(actor, child, position) != 0) {
    return;
  }
  *((u16 *) child) = gMainWorkspace.field18C2;
  if (sub_08003740(((s8 *) work) + 0x20, child) == 0) {
    sub_080C31E0(actor, *((s32 *) (((s8 *) actor) + 0x24)));
    return;
  }
  sub_0806D588(child, position);
  if (gMainWorkspace.field173A == 0x1C) {
    sub_080C31E0(actor, *((s32 *) (((s8 *) actor) + 0x24)));
    return;
  }
  if (gMainWorkspace.field14ED == 0 && gMainWorkspace.field10 != 0) {
    sub_080C31E0(actor, *((s32 *) (((s8 *) actor) + 0x24)));
    return;
  }
  sub_0806D2F8(actor, child);
}
