s32 sub_0801165C(void *, s32);
s32 sub_0805F9B4(s32, s32);
s32 sub_080C31E0(void *, void *);

struct S_02025FF0_18A8 { u8 _0x000[0x18A8]; u8 cameraIndex; };
extern struct S_02025FF0_18A8 D_02025FF0;
extern u8 D_02021E90[];

/* Actor update: switch state when out of view, otherwise integrate motion and
 * recompute the sprite's screen coordinates from the camera table. */
void sub_08054DFC(void *entity)
{
  void *self = entity;
  void *sprite;
  void *work;
  u8 *coordTable;
  u32 coordOffset;
  u8 *xBase;
  u8 *yBase;

  sprite = *((void **) (((u8 *) self) + 0x38));
  work = *((void **) (((u8 *) self) + 0x3C));

  if (sub_0805F9B4(*((s32 *) (((u8 *) work) + 0x08)), *((s32 *) (((u8 *) work) + 0x0C))) == 1)
  {
    sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24)));
    return;
  }

  sub_0801165C(work, 0x16C1);

  coordTable = D_02021E90;
  coordOffset = (D_02025FF0.cameraIndex + 1) * 0x40;
  xBase = coordTable + 0x1278;
  *((s32 *) (((u8 *) sprite) + 0x14)) = (*((s32 *) (((u8 *) work) + 0x08))) - ((*((s32 *) (xBase + coordOffset)) + 0x8000) & 0xFFFF0000);

  coordOffset = (D_02025FF0.cameraIndex + 1) * 0x40;
  yBase = coordTable + 0x127C;
  *((s32 *) (((u8 *) sprite) + 0x18)) = (*((s32 *) (((u8 *) work) + 0x0C))) - ((*((s32 *) (yBase + coordOffset)) + 0xFFFF8000) & 0xFFFF0000);
}
