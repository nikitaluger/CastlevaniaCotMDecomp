void sub_080AC9B4(u8, void *);
void sub_080ACCA4(s32, void *, void *, void *);
s32 signOf(s32);
void setSpriteFacingToTarget(void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Set up a tracking actor: prepare both facing animations, compute its direction toward the target, and when nonzero pick the facing animation and finish the state. */
void sub_080ABE68(void *arg0)
{
  void *gfx;
  void *entity;
  void *state;
  void *anim;
  s32 direction;
  s32 *cbTable;
  gfx = *((void **) (((u8 *) arg0) + 0x38));
  entity = *((void **) (((u8 *) arg0) + 0x3C));
  state = ((u8 *) entity) + 0x48;
  sub_080AC9B4(*((u8 *) (((u8 *) entity) + 0x244)), ((u8 *) entity) + 0x68);
  anim = ((u8 *) entity) + 0x98;
  sub_080ACCA4(0, gfx, entity, anim);
  sub_080ACCA4(1, gfx, entity, anim);
  direction = signOf(*((s32 *) (((u8 *) entity) + 8)));
  *((s8 *) (((u8 *) entity) + 0xC6)) = (s8) direction;
  if ((direction << 17) << 7)
  {
    *((s8 *) (((u8 *) entity) + 0xC6)) = 1;
    setSpriteFacingToTarget(gfx, *((s32 *) (((u8 *) entity) + 8)));
    *((s8 *) (((u8 *) state) + 0x1D)) = (*((u16 *) (((u8 *) gfx) + 2)) & 0x10) ? 1 : -1;
    *((s8 *)(((s16 *)((u8 *)arg0 + 0x22))[0] * 2 + (u8 *)arg0 + 0x19)) = 0;
    cbTable = (s32 *) 0x08671BB0;
    sub_080C31E4((u8 *) arg0 + 0x18, (u8 *) arg0 + 0x22, *cbTable);
  }
}
