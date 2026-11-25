inline s8 *asBytePtr(void *arg0)
{
  return (s8 *) arg0;
}

inline u8 firstByte(s8 *arg0)
{
  return *((u8 *) arg0);
}

/* Reposition this actor's sprite for the linked object: set (state 2 or 4) or
 * clear the sprite's X-flip bit 0x40, install gfx descriptor 0x0863E89C, and
 * place the sprite at X = linked[0x58] (signed) * 12 pixels, Y = 0. */
void sub_0800C2C8(void *arg0)
{
  u8 *attr;
  s32 value;
  s8 linkedState;
  void *sprite;
  sprite = *((void **) (((s8 *) arg0) + 0x38));
  linkedState = (s8) firstByte(((s8 *) (*((void **) (asBytePtr(arg0) + 0x28)))) + 0x4C);
  if ((linkedState == 2) || (linkedState == 4))
  {
    attr = (u8 *)((s8 *)sprite + 0x2A);
    value = 0x40 | *attr;
    *attr = value;
  }
  else
  {
    attr = (u8 *)((s8 *)sprite + 0x2A);
    value = 0xBF & *attr;
    *attr = value;
  }
  *((s32 *) (((s8 *) sprite) + 0x24)) = 0x0863E89C;
  *((s32 *) (asBytePtr(sprite) + 0x14)) = (s32) ((*asBytePtr(asBytePtr(*((void **) (asBytePtr(arg0) + 0x28))) + 0x58)) * 0xC0000);
  *((s32 *) (((s8 *) sprite) + 0x18)) = 0;
}
