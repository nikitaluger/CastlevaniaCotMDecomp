struct GameState
{
  u8 _p[0x10];
  s32 field10;
  u8 _a[0x14ED - 0x14];
  u8 field14ED;
  u8 _b[0x14FC - 0x14EE];
  s32 field14FC;
  u8 _c[0x173A - 0x1500];
  u8 field173A;
  u8 _d[0x18A8 - 0x173B];
  u8 field18A8;
};
extern struct GameState gMainWorkspace;
extern u8 gTilemapPages[];
s32 sub_0806D450(void *, void *, void *);
void sub_0806D588(void *, void *);
s16 sub_08007DD8(u8 *, s32, s32);
void sub_0806E114(s32, s32, s32, s32);
void sub_0806D2F8(void *, void *);
void sub_080C31E0(void *, void *);

/* One frame of a scripted actor: apply camera/movement overrides, advance its
 * position, then spawn an effect on collision or choose between aborting the
 * script and running the off-screen check. */
void sub_080708D8(u8 *arg0)
{
  u8 *actor = *(u8 **)(arg0 + 0x6C);
  u8 *mover = actor + 4;
  u8 *world = *(u8 **)(arg0 + 0x38);
  s16 hitType;
  if (sub_0806D450(arg0, world, mover) > 0) goto abort;
  *(s32 *)(actor + 4) += *(s32 *)(mover + 8);
  sub_0806D588(world, mover);
  if ((*(u16 *)(*((u8 **)(mover + 0x3C)) + 0x14) & 1) == 0) goto checkCollision;
spawnEffect:
  sub_0806E114(*(s32 *)(arg0 + 0x28), 8, *(s32 *)(actor + 4), *(s32 *)(mover + 4));
  goto abort;
checkCollision:
  hitType = sub_08007DD8(gTilemapPages + (gMainWorkspace.field18A8 << 6), *(s32 *)(actor + 4), *(s32 *)(mover + 4));
  if (hitType != 0) goto spawnEffect;
  if (gMainWorkspace.field14FC != 0) goto abort;
  if (gMainWorkspace.field173A == 0x1C) goto abort;
  if (gMainWorkspace.field14ED != 0) goto offscreen;
  if (gMainWorkspace.field10 == 0) goto offscreen;
  goto abort;
abort:
  sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
  return;
offscreen:
  sub_0806D2F8(arg0, world);
}
