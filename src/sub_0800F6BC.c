extern void sub_080063D4(u32 *arg0, void *arg1);
extern volatile int sub_08000E98(void *a, void *b, void *c, u32 d, u32 e);
extern volatile int sub_08000E54(void *a, void *b, void *c, u32 d, u32 e);
extern u8 D_02025368[];
extern s8 D_020278D0[];
extern u32 D_0866CFEC[];
extern u32 D_0866D03C[];

/* Loads a room's compressed tiles and palette when its flag is set in the map
 * state, otherwise queues a VRAM clear. */
void sub_0800F6BC(void)
{
  int rowBias;
  int listKey;
  s32 column;
  s8 row;
  s32 off;
  s32 gfxColumn;
  s32 gfxOffset;
  s32 paletteColumn;
  s32 paletteOffset;
  u8 *state = D_02025368;
  u8 *roomFlags;
  u8 *gfxTable;
  u8 *paletteTable;
  listKey = 0xFA;
  column = D_020278D0[listKey];
  row = D_020278D0[0xF9];
  rowBias = (((row + 1) & 1) * 10) - 1;
  off = column + rowBias;
  roomFlags = state + 0x30C;
  if (roomFlags[off] != 0)
  {
    gfxTable = (u8 *)D_0866CFEC;
    gfxColumn = column - 1;
    gfxOffset = gfxColumn * 4;
    gfxOffset += row * 40;
    sub_080063D4(*(u32 **)(gfxTable + gfxOffset), (void *)0x0600D300);
    listKey = 1;
    sub_08000E98((void *)listKey, (void *)0x0600D300, (void *)0x0600C300, 0xC00, 0x10);
    paletteTable = (u8 *)D_0866D03C;
    paletteColumn = D_020278D0[0xFA] - listKey;
    paletteOffset = paletteColumn * 4;
    paletteOffset += D_020278D0[0xF9] * 40;
    sub_08000E98((void *)listKey, (void *)(*(u32 **)(paletteTable + paletteOffset)), (void *)0x050000E0, 0x20, 0x10);
  }
  else
  {
    sub_08000E54((void *)1, (void *)0, (void *)0x0600C300, 0xC00, 0x10);
  }
}
