struct S_02025FF0
{
  u8 _0x000[0x10];
  s32 flags10;
  u8 _0x014[0x14ED - 0x14];
  u8 state14ED;
  u8 _0x14EE[0x173A - 0x14EE];
  u8 state173A;
  u8 _0x173B[0x18C2 - 0x173B];
  u16 gfxFlag;
};
extern struct S_02025FF0 gMainWorkspace;
s32 sub_0806D450(void *, void *, void *);
void sub_08003740(void *, void *);
void sub_0806D2F8(void *, void *);
void sub_080C31E0(void *, s32);
/* Advances the entity's motion by its scripted velocity, syncs its sprite,
 * then either keeps it running or hands control back to the script state when
 * the motion routine, the room change or the state flags say so. */
void sub_08082938(void *arg0)
{
  void *child;
  void *motion;
  void *sprite;
  child = *((void **) (((s8 *) arg0) + 0x6C));
  motion = ((s8 *) child) + 4;
  sprite = *((void **) (((s8 *) arg0) + 0x38));
  if (((sub_0806D450(arg0, sprite, motion) > 0) || ((*((s32 *) (((s8 *) sprite) + 0x14)) = (*((s32 *) (((s8 *) sprite) + 0x14))) + (*((s32 *) (((s8 *) motion) + 8))), *((s32 *) (((s8 *) sprite) + 0x18)) = (*((s32 *) (((s8 *) sprite) + 0x18))) + (*((s32 *) (((s8 *) motion) + 0xC))), *((u16 *) sprite) = gMainWorkspace.gfxFlag, sub_08003740(((s8 *) child) + 0x20, sprite), gMainWorkspace.state173A == 0x1C))) || ((gMainWorkspace.state14ED == 0) && (gMainWorkspace.flags10 != 0)))
  {
 do { sub_080C31E0(arg0, *((s32 *) (((s8 *) arg0) + 0x24))); } while (0);
  }
  else
  {
    sub_0806D2F8(arg0, sprite);
  }
}
