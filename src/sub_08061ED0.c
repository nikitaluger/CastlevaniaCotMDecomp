struct S_02027A00
{
  u8 pad[0x12];
  u8 cursorX;
  u8 cursorY;
  u16 frame;
};
extern struct S_02027A00 D_02027A00;
struct S_02021E90
{
  u8 pad[0x1278];
  u32 scrollX;
  u32 scrollY;
};
extern struct S_02021E90 D_02021E90;

/*
 * Position a scrolling-screen cursor sprite: convert its grid coordinate minus
 * the camera scroll into a fixed-point position, set its graphics table pointer
 * and size from the frame counter, set flag 0x400, and advance the counter.
 */
void sub_08061ED0(u8 *sprite)
{
  u32 x;
  u32 y;
  u32 sx;
  u32 sy;
  int tmp;
  u32 bias;
  x = D_02027A00.cursorX << 0x12;
  sx = D_02021E90.scrollX;
  bias = 0xFFFE8000;
  *((s32 *)(sprite + 0x14)) = x - (sx + bias);
  y = D_02027A00.cursorY << 0x12;
  sy = D_02021E90.scrollY;
  *((s32 *)(sprite + 0x18)) = y - (sy + bias);
  *((u32 *)(sprite + 0x24)) = 0x084541A8;
  {
    u16 f = D_02027A00.frame;
    s32 size = ((f & 0x3F) << 4) + 0x80;
    *((u16 *)(sprite + 0x04)) = size;
    *((u16 *)(sprite + 0x06)) = size;
    *((u16 *)(sprite + 0x02)) = (tmp = 0x400 | (*((u16 *)(sprite + 0x02))));
    D_02027A00.frame = f + 1;
  }
}
