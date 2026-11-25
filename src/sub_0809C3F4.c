/* Sync two linked entities: set both facings from a flag, pick a linked state from the current animation frame, and copy shared coordinates when it is a valid link frame. */
void sub_0809C3F4(s32 *entities, u16 *flags, s32 *coords, u8 *animState)
{
  s32 entity;
  s32 *frameTable;
  s32 frameIndex;
  s32 tableBase;
  u32 addr;
  u16 *framePtr;
  u16 frame;
  s32 direction;
  entity = entities[0];
  if (entity == 0) return;
  if (entities[1] == 0) return;
  if ((*(volatile u16 *)(flags + 1)) & 0x10) direction = 1; else direction = -1;
  *(s32 *)(entity + 0x6C) = direction;
  entity = entities[1];
  if ((*(volatile u16 *)(flags + 1)) & 0x10) direction = 1; else direction = -1;
  *(s32 *)(entity + 0x6C) = direction;
  frameTable = *(s32 **)((u8 *)animState + 8);
  frameIndex = (s32)*(s16 *)((u8 *)animState + 0x0E) + (s32)*((u8 *)animState + 1);
  tableBase = *frameTable;
  addr = frameIndex << 2;
  addr += (u32)tableBase;
  framePtr = (u16 *)(addr - 4);
  frame = framePtr[1];
  switch (frame) {
    case 0x5E:
      *(u8 *)(entities[0] + 0x7C) = 1;
      *(u8 *)(entities[1] + 0x7C) = 1;
      break;
    case 0x8F:
      *(u8 *)(entities[0] + 0x7C) = 2;
      *(u8 *)(entities[1] + 0x7C) = 2;
      break;
    default:
      *(u8 *)(entities[0] + 0x7C) = 0;
      *(u8 *)(entities[1] + 0x7C) = 0;
      return;
  }
  *(s32 *)(entities[0] + 0x4C) = coords[2];
  *(s32 *)(entities[0] + 0x5C) = coords[3];
  *(s32 *)(entities[1] + 0x4C) = coords[2];
  *(s32 *)(entities[1] + 0x5C) = coords[3];
}
