extern u16 D_080CB224[];
extern u8 D_086426B4[];
extern union {
    u8 b[0x800];
    s8 sb[0x800];
} gMenuState;
inline u16 inline_fn(u32 base, int index)
{
  return *((u16 *) (base + index));
}

/* Pick an 8-byte graphics record for the actor's sprite out of the D_080CB224
 * table, then set or clear the sprite's highlight bit (0x40) according to a
 * comparison of two runtime state values. */
void sub_0800FAE4(u8 *actor)
{
  u32 gfxTable;
  u8 *kindPtr;
  s8 kind;
  u32 gfxOff;
  s8 kindValue;
  u8 stateVal;
  s8 stateSigned;
  s8 stateIndex;
  s32 diff;
  u8 *flagPtr;
  u8 flags;
  u32 sprite;

  sprite = *((u32 *) (actor + 0x38));
  gfxTable = (u32) D_080CB224;
  kindPtr = actor + 0x44;
  kind = ((s8 *) kindPtr)[0];
  gfxOff = ((u32) inline_fn(gfxTable, ((u32) kind) * 2)) << 3;
  *((u32 *) (sprite + 0x24)) = (u32) (D_086426B4 + gfxOff);
  kindValue = (s8) kindPtr[0];
  if (kindValue == 0)
  {
    stateIndex = (s8) gMenuState.b[0x6A];
    stateSigned = ((s8 *) ((gMenuState.b + 0x6F) + stateIndex))[0];
    if (stateSigned > 0)
    {
      flagPtr = (u8 *) (sprite + 0x2A);
      flags = (*flagPtr) | 0x40;
      *flagPtr = flags;
      return;
    }
  }
  else
  {
    stateIndex = gMenuState.sb[0x6A];
    stateVal = *(u8 *) (gMenuState.b + 0x6A + 0x89 + stateIndex);
    stateSigned = ((s8 *) ((gMenuState.b + 0x6F) + stateIndex))[0];
    diff = stateVal - stateSigned;
    if (diff > 8)
    {
      flagPtr = (u8 *) (sprite + 0x2A);
      flags = (*flagPtr) | 0x40;
      *flagPtr = flags;
      return;
    }
  }
  flagPtr = (u8 *) (sprite + 0x2A);
  flags = (*flagPtr) & 0xBF;
  *flagPtr = flags;
}
