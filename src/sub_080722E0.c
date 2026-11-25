extern s32 D_0866EF18[]; /* sine values (fixed point) */
extern u8 D_0866F01C[]; /* angle -> sine-table index (0..0x40, mirrored) */

/* Direction-vector command: expand the packed angle byte (bit 0x80 is the
 * vertical sign) into cosine/sine components with D_0866F01C/D_0866EF18 and
 * store them at target+8 (X) and target+0xC (Y). */
void sub_080722E0(void *arg0, u8 arg1)
{
  u8 index = arg1 & 0x7F;
  s32 sinComp = D_0866EF18[D_0866F01C[index]];
  s32 cosComp;
  if (arg1 & 0x80) sinComp = -sinComp;
  cosComp = D_0866EF18[D_0866F01C[index + 0x40]];
  if ((u8)(arg1 - 0x41) <= 0x7E) cosComp = -cosComp;
  *(s32 *)((u8 *)arg0 + 8) = cosComp;
  *(s32 *)((u8 *)arg0 + 0xC) = sinComp;
}
