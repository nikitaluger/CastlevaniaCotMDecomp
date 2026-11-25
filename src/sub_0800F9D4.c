extern s8 D_020278D0[];
extern u16 D_080CB200[];
extern u8 D_086426B4[];

/* Set the sprite's 0x40 flag and point its graphic at the tile data for
 * the object's facing, choosing the mirrored variant when the facing
 * differs from the global facing flag at D_020278D0+0x68. */
void sub_0800F9D4(u8 *obj)
{
  u8 *sprite;
  s8 *facingFlag;
  s8 globalDir;
  s8 objDir;
  s32 diff;
  s32 mirrored;
  s32 dir;
  s32 tileOfs;
  u16 tile;
  u8 *tiles;
  s32 flags;
  sprite = *(u8 **)(obj + 0x38);
  flags = 0x40 | *(sprite + 0x2A);
  *(sprite + 0x2A) = flags;
  facingFlag = D_020278D0;
  facingFlag += 0x68;
  globalDir = *facingFlag;
  objDir = *((s8 *)(obj + 0x44));
  diff = globalDir ^ objDir;
  mirrored = ((u32)((-diff) | diff)) >> 31;
  tiles = (u8 *)D_080CB200;
  mirrored <<= 1;
  dir = (s8)*((u8 *)(obj + 0x44));
  tileOfs = mirrored + (dir << 2);
  tile = *((u16 *)(tiles + tileOfs));
  *((u32 *)(sprite + 0x24)) = (tile << 3) + (u32)(&D_086426B4);
}
