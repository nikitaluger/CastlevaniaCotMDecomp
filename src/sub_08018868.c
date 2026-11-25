/* Update the sprite's on-screen flag, fixed-point position and horizontal flip
 * from the entity's state, then convert that position into room-local screen
 * coordinates using the current room's scroll offsets. */
s32 sub_0805F9B4(s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
void sub_08018868(void *entity)
{
  void *gfx;
  void *motion;
  u8 *visibleFlag;
  u8 *roomData;
  u8 *roomIdx;
  s32 flipBit;
  u8 *scrollX;
  u8 *scrollY;
  u32 roomOffset;
  gfx = *((void **) (((u8 *) entity) + 0x38));
  motion = *((void **) (((u8 *) entity) + 0x3C));
  flipBit = 0x10;
  if (sub_0805F9B4(*((s32 *) (((u8 *) motion) + 8)), *((s32 *) (((u8 *) motion) + 0xC))) == 1)
  {
    visibleFlag = ((u8 *) gfx) + 0x2A;
    *visibleFlag &= 0xBF;
  }
  else
  {
    s32 flags;
    visibleFlag = ((u8 *) gfx) + 0x2A;
    flags = 0x40 | *visibleFlag;
    *visibleFlag = flags;
  }
  *((u32 *) (((u8 *) motion) + 8)) = (*((s16 *) (((u8 *) entity) + 0x4C))) << 16;
  *((u32 *) (((u8 *) motion) + 0xC)) = (*((s16 *) (((u8 *) entity) + 0x54))) << 16;
  if ((*((s16 *) (((u8 *) entity) + 0x5C))) < 0)
  {
    *((u16 *) (((u8 *) gfx) + 2)) = 0xFFEF & (*((u16 *) (((u8 *) gfx) + 2)));
  }
  else
  {
    *((u16 *) (((u8 *) gfx) + 2)) = flipBit | (*((u16 *) (((u8 *) gfx) + 2)));
  }
  roomData = D_02021E90;
  roomIdx = D_02025FF0;
  roomIdx += 0x18A8;
  roomOffset = (((u32) (*roomIdx)) + 1) * 0x40;
  scrollX = roomData + 0x1278;
  *((u32 *) (((u8 *) gfx) + 0x14)) = (*((u32 *) (((u8 *) motion) + 8))) - (((*((s32 *) (roomOffset + ((u32) scrollX)))) + 0x8000) & 0xFFFF0000);
  roomOffset = (((u32) (*roomIdx)) + 1) * 0x40;
  scrollY = roomData + 0x127C;
  *((u32 *) (((u8 *) gfx) + 0x18)) = (*((u32 *) (((u8 *) motion) + 0xC))) - (((*((s32 *) (roomOffset + ((u32) scrollY)))) + 0xFFFF8000) & 0xFFFF0000);
}
