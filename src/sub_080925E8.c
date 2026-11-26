extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080113A8(u8 *, u8 *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866F9E8[];
struct SpriteFlags { u8 value; };

/* Updates an entity's sprite state and world position: syncs animation and
 * timer fields, advances the index, dispatches the table callback selected by
 * that index, then snaps the sprite to the coordinate table when its flag bit
 * is clear. */
void sub_080925E8(u8 *entity)
{
  u32 fixedMask;
  u8 *obj;
  u8 *state;
  u8 *target;
  s32 result;
  u8 *entry;
  u8 *coordBase;
  u8 *xTable;
  u8 *indexPtr;
  u32 coordIdx;
  u32 xAdjust;
  u32 yAdjust;
  u32 callbackIdx;
  u8 *callbackBase;
  s32 entryOffset;
  u8 *destObj;
  obj = *((u8 **) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  target = state + 0x24;
  result = sub_0805F9B4(*((s32 *) (state + 0x04)), *((s32 *) (state + 0x08)));
  if (result == 1)
  {
    ((struct SpriteFlags *) (obj + 0x2A))->value &= 0xBF;
  }
  else
  {
    ((struct SpriteFlags *) (obj + 0x2A))->value |= 0x40;
  }
 do { destObj = *((u8 **) (state + 0x20)); fixedMask = 0xFFFF0000; *((u16 *) (destObj + 0x06)) = *((u16 *) (state + 0x16)); *((u32 *) (state + 0x18)) = *((u32 *) (state + 0x14)); if ((*((s16 *) (state + 0x10))) > 0) { *((s16 *) (state + 0x10)) = (*((s16 *) (state + 0x10))) - 1; } *((u32 *) (entity + 0x14)) = (u32) D_0866F9E8; *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1; entry = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)); *((u8 *) (entry + 0x19)) = (*((u8 *) (entry + 0x19))) + 1; entryOffset = (*((s16 *) (entity + 0x22))) * 2; callbackBase = entity; callbackBase += 0x18; callbackIdx = *((u8 *) (((u32) callbackBase) + ((u32) entryOffset))); } while (0);
  sub_080C31E0((s32) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (callbackIdx * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  entryOffset = 0;
  if (((*((u16 *) (entity + 2))) & 0x8000) == entryOffset)
  {
    if ((*((s16 *) (state + 0x0C))) == 1)
    {
      sub_080113A8(obj, target);
    }
    *((u16 *) (state + 0x0E)) = 0;
    coordBase = gCameraState;
    indexPtr = gMainWorkspace;
    indexPtr += 0x18A8;
    coordIdx = (((u32) (*indexPtr)) + 1) * 0x40;
    xTable = coordBase + 0x1278;
    xAdjust = *((u32 *) (xTable + coordIdx));
    *((u32 *) (obj + 0x14)) = (*((u32 *) (state + 0x04))) - ((xAdjust + 0x8000) & fixedMask);
    coordIdx = (((u32) (*indexPtr)) + 1) * 0x40;
    coordBase += 0x127C;
    yAdjust = *((u32 *) (coordBase + coordIdx));
    *((u32 *) (obj + 0x18)) = (*((u32 *) (state + 0x08))) - ((yAdjust + 0xFFFF8000) & fixedMask);
  }
}
