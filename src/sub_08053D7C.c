s32 getSpriteFacingSign(s32);
void spawnVariant2Effect(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* Spawn effect 0x203 to the side of this entity (which side depends on the
 * facing bit in its graphics header) and slightly below it, then run the
 * entity's current state handler. */
void sub_08053D7C(void *arg0)
{
  u8 *work;
  s32 gfx;
  gfx = *((s32 *) (((u8 *) arg0) + 0x38));
  work = *((u8 **) (((u8 *) arg0) + 0x3C));
  if (getSpriteFacingSign(gfx) < 0)
  {
    spawnVariant2Effect((*((s32 *) (work + 8))) + 0xFFF20000, (*((s32 *) (work + 0xC))) + 0x80000, 8);
  }
  else
  {
    spawnVariant2Effect((*((s32 *) (work + 8))) + 0xE0000, (*((s32 *) (work + 0xC))) + 0x80000, 8);
  }
  sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
}
