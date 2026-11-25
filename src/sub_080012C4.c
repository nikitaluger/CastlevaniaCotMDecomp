/* Object pool: fixed 0xBC-byte records starting at D_02004460. D_02025B7C
 * holds the pool start, D_02025B78 the pool end and D_02025740 the number of
 * records requested by the last init call. */
extern u32 D_02004460;
extern u32 D_02025740;
extern u32 D_02025B78;
extern u32 D_02025B7C;
void sub_080013D0(void);

/* Size the object pool for `recordCount` 0xBC-byte records and reset it,
 * then return the record count. */
s32 sub_080012C4(s32 recordCount)
{
  u32 poolBase = (u32) (&D_02004460);
  D_02025B7C = (u32) (&D_02004460);
  D_02025B78 = recordCount;
  D_02025740 = recordCount;
  D_02025740 = recordCount;
  D_02025B78 = (D_02025B78 * 0xBC) + ((u32) (&D_02004460));
  sub_080013D0();
  if (1)
  {
    return D_02025740;
  }
}
