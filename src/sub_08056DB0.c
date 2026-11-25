void sub_08011368(s32, void *, s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080553D4(void *arg0);

/* Orbit a sprite around a pivot: advance the work angle by deltaAngle, then
 * store the pivot (obj+0x4C/0x5C) offset by a sine/cosine rotation of that
 * angle, scaled by the fixed-point (8.8) radius at work+0x18. */
void sub_08056DB0(void *obj, void *sprite, void *work, s32 deltaAngle)
{
  s32 sinScaled;
  s32 angle = (*((s32 *) (((u8 *) work) + 0x14))) + deltaAngle;
  void **trig;
  s32 scaled;
  *((s32 *) (((u8 *) work) + 0x14)) = angle;
  trig = (void **) 0x08671BFC;
  sinScaled = sub_080C31E0(angle + 0x4000, (s32) (*trig)) >> 8;
  scaled = sinScaled;
  *((s32 *) (((u8 *) sprite) + 8)) = (*((s32 *) (((u8 *) obj) + 0x4C))) + (scaled * ((*((s32 *) (((u8 *) work) + 0x18))) >> 8));
  scaled = sub_080C31E0(*((s32 *) (((u8 *) work) + 0x14)), (s32) (*trig)) >> 8;
  *((s32 *) (((u8 *) sprite) + 0xC)) = (*((s32 *) (((u8 *) obj) + 0x5C))) - (scaled * ((*((s32 *) (((u8 *) work) + 0x18))) >> 8));
}
