extern u8 gGameStatus[];

/* Return the graphic-present flag for character `charId` (0..7), used to
 * decide whether that character's tiles and palette should be loaded. */
u8 sub_0800F414(s8 charId)
{
  u8 *flags = gGameStatus;
  u8 *tbl[8] = {
    flags + 0x3C7, flags + 0x3C8, flags + 0x3C9, flags + 0x3CA,
    flags + 0x3CB, flags + 0x3CC, flags + 0x3CD, flags + 0x3CE
  };
  return *tbl[charId];
}
