extern u32 D_0866CA14;
s32 sub_080C31E4(void *, s32, s32);

/* Delay timer: count down the u16 at obj+2. Returns 0 when it was already spent,
 * 1 while it is still running, and when it expires dispatches the handler
 * D_0866CA14[obj->byte0] with (obj, arg). */
s32 stepDelayTimer(void *arg0, s32 arg1)
{
  u32 count = *(u16 *)((u8 *)arg0 + 0x02);
  if (count == 0)
    return 0;
  count--;
  *(u16 *)((u8 *)arg0 + 0x02) = (u16)count;
  if ((count << 16) != 0)
    return 1;
  {
    s32 *tbl = (s32 *)&D_0866CA14;
    return sub_080C31E4(arg0, arg1, tbl[*(u8 *)arg0]);
  }
}
