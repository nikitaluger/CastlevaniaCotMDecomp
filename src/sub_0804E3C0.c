s32 getSpriteFacingSign(s32);
s32 sub_0808DC40(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* Spawn effect 0x203 half a unit to the side of this entity (which side
 * depends on the facing bit its graphics header reports) and slightly
 * below it, then run the entity's current state handler. */
void sub_0804E3C0(void *arg0)
{
  s32 gfx;
  s32 x;
  u8 *work;

  gfx = *((s32 *) (((u8 *) arg0) + 0x38));
  work = *((u8 **) (((u8 *) arg0) + 0x3C));
  if (getSpriteFacingSign(gfx) < 0)
  {
    sub_0808DC40((*((s32 *) (work + 8))) + 0xFFF80000, (*((s32 *) (work + 0xC))) + 0xFFF80000, 8);
  }
  else
  {
    x = *((s32 *) (work + 8));
    sub_0808DC40(x + 0x80000, (*((s32 *) (work + 0xC))) + 0xFFF80000, 8);
  }
  sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
}
