extern s8 gMenuState[];
extern u16 D_080CB214[];
extern u8 D_086426B4[];

/* Set a display flag on the actor's sprite, then point its graphics at the
 * 8-byte entry selected by its direction byte (and whether that direction
 * matches the global facing value). */
void sub_0800FA24(u8 *actor)
{
  u8 *sprite;
  s8 *facingPtr;
  s8 globalFacing;
  s8 dir;
  s32 diff;
  s32 signBit;
  s32 dirSign;
  s32 idx;
  u16 val;
  u8 *tbl;
  s32 orv;
  sprite = *(u8 **)(actor + 0x38);
  orv = 0x40 | *(sprite + 0x2A);
  *(sprite + 0x2A) = orv;
  facingPtr = gMenuState;
  facingPtr += 0x6A;
  globalFacing = *facingPtr;
  dir = *((s8 *)(actor + 0x44));
  diff = globalFacing ^ dir;
  signBit = ((u32)((-diff) | diff)) >> 31;
  tbl = (u8 *)D_080CB214;
  signBit <<= 1;
  dirSign = (s8)*((u8 *)(actor + 0x44));
  idx = signBit + (dirSign << 2);
  val = *((u16 *)(tbl + idx));
  *((u32 *)(sprite + 0x24)) = (val << 3) + (u32)(&D_086426B4);
}
