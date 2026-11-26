s32 signOf(s32);
s32 sub_08014990(s32);
void setAnimationFrame(s32, s32, s32, s32);
void sub_080C31E8(void *, void *, s32, s32);
struct DirExtra { u8 unk0[2]; u16 choice; u8 unk4[0x36]; };

/* Advance the animation to frame 13; when its flag 2 is set, compare a signed
 * direction against the sprite's facing sign and start one of two scripts. */
void sub_0803D9E4(void *arg0)
{
  s32 zero;
  s32 *pValue;
  u8 *self = arg0;
  void *sprite;
  void *state;
  struct DirExtra *extra;
  s32 dirSign, facingSign;
  s32 *pScript;
  s16 index;
  u8 *slot;
  sprite = *((void **) (self + 0x38));
  state = *((void **) (self + 0x3C));
  arg0 = ((u8 *) state) + 0x34;
  extra = (struct DirExtra *) (((u8 *) state) + 0x48);
  pValue = ((u8 *) state) + 8;
  setAnimationFrame((s32) sprite, (s32) arg0, 0x0D, 0);
  zero = 0;
  *((s32 *) (((u8 *) state) + 0x10)) = zero | 0;
  if (((u8 *) arg0)[0] & 2)
  {
    dirSign = signOf(*((s32 *) pValue));
    facingSign = sub_08014990((s32) sprite);
    if (dirSign == facingSign)
    {
      extra->choice = 1;
      index = *((s16 *) (self + 0x22));
      slot = (u8 *) ((index * 2) + ((u32) self));
      *((u8 *) (slot + 0x17)) = 0;
      pScript = &(*((s32 *) 0x08671BD8));
      sub_080C31E8(self + 0x18, self + 0x22, 2, *pScript);
    }
    else
    {
      extra->choice = zero;
      index = *((s16 *) (self + 0x22));
      slot = (u8 *) ((index * 2) + ((u32) self));
      *((u8 *) (slot + 0x17)) = 0;
      pValue = (s32 *) 0x08671BD8;
      sub_080C31E8(self + 0x18, self + 0x22, 3, *pValue);
    }
  }
}
